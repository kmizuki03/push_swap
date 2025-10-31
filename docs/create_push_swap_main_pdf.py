import os
import textwrap
from typing import List

INPUT_MD = "push_swap_main_beginner_guide.md"
OUTPUT_PDF = "push_swap_main_beginner_guide.pdf"
PAGE_WIDTH = 612  # points (US Letter)
PAGE_HEIGHT = 792
LEFT_MARGIN = 72
TOP_MARGIN = 720
BOTTOM_MARGIN = 72
FONT_SIZE = 12
LINE_HEIGHT = 14  # leading used with TL command
MAX_LINES_PER_PAGE = int((TOP_MARGIN - BOTTOM_MARGIN) / LINE_HEIGHT) + 1


def markdown_to_lines(markdown_text: str) -> List[str]:
    lines: List[str] = []
    for raw_line in markdown_text.splitlines():
        line = raw_line.strip()
        if not line:
            lines.append("")
            continue
        # Headings
        if line.startswith("#"):
            level = len(line) - len(line.lstrip("#"))
            heading = line[level:].strip()
            heading = heading.replace("`", "")
            lines.append(heading.upper())
            continue
        # Bullet lists
        bullet = ""
        if line.startswith(('- ', '* ')):
            bullet = "・"
            line = line[2:].strip()
        elif any(line.startswith(f"{n}. ") for n in range(1, 10)):
            bullet = "・"
            line = line[line.find(" ")+1:].strip()
        # Inline formatting cleanup
        for pattern in ["**", "__", "`"]:
            line = line.replace(pattern, "")
        line = line.replace("\\n", " ")
        wrapped = textwrap.wrap(line, width=80) or [""]
        if bullet:
            first = True
            for segment in wrapped:
                prefix = f"{bullet} " if first else "  "
                lines.append(prefix + segment)
                first = False
        else:
            lines.extend(wrapped)
    return lines


def escape_pdf_text(text: str) -> str:
    return text.replace("\\", "\\\\").replace("(", "\\(").replace(")", "\\)")


def chunk_lines(lines: List[str]) -> List[List[str]]:
    pages: List[List[str]] = []
    current: List[str] = []
    for line in lines:
        if len(current) >= MAX_LINES_PER_PAGE:
            pages.append(current)
            current = []
        current.append(line)
    if current:
        pages.append(current)
    return pages


def build_content_stream(lines: List[str]) -> bytes:
    content_lines = ["BT", "/F1 12 Tf", f"1 0 0 1 {LEFT_MARGIN} {TOP_MARGIN} Tm", f"{LINE_HEIGHT} TL"]
    first = True
    for line in lines:
        text = escape_pdf_text(line)
        if first:
            content_lines.append(f"({text}) Tj")
            first = False
        else:
            content_lines.append("T*")
            content_lines.append(f"({text}) Tj")
    content_lines.append("ET")
    content = "\n".join(content_lines)
    return content.encode("utf-8")


def write_pdf(pages: List[List[str]], output_path: str) -> None:
    objects: List[bytes] = []
    # 1: Catalog, 2: Pages, 3..2+n: Page objects, 3+n..2+2n: Contents, last: Font
    n_pages = len(pages)
    font_obj_number = 3 + 2 * n_pages

    # Placeholder for page and content objects
    page_objects: List[bytes] = []
    content_objects: List[bytes] = []
    for page_index, lines in enumerate(pages):
        content_stream = build_content_stream(lines)
        content_obj = (
            f"{3 + n_pages + page_index} 0 obj\n"
            f"<< /Length {len(content_stream)} >>\n"
            f"stream\n".encode("utf-8")
            + content_stream
            + "\nendstream\nendobj\n".encode("utf-8")
        )
        content_objects.append(content_obj)

        page_obj = (
            f"{3 + page_index} 0 obj\n"
            "<< /Type /Page /Parent 2 0 R "
            f"/MediaBox [0 0 {PAGE_WIDTH} {PAGE_HEIGHT}] "
            f"/Contents {3 + n_pages + page_index} 0 R "
            f"/Resources << /Font << /F1 {font_obj_number} 0 R >> >> >>\nendobj\n"
        ).encode("utf-8")
        page_objects.append(page_obj)

    pages_kids = "[ " + " ".join(f"{3 + i} 0 R" for i in range(n_pages)) + " ]"
    pages_obj = (
        f"2 0 obj\n<< /Type /Pages /Count {n_pages} /Kids {pages_kids} >>\nendobj\n"
    ).encode("utf-8")

    catalog_obj = b"1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
    font_obj = (
        f"{font_obj_number} 0 obj\n<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\nendobj\n"
    ).encode("utf-8")

    # Combine objects in order
    objects.append(catalog_obj)
    objects.append(pages_obj)
    objects.extend(page_objects)
    objects.extend(content_objects)
    objects.append(font_obj)

    # Write PDF with xref
    pdf_bytes = bytearray(b"%PDF-1.4\n")
    offsets = [0]
    for obj in objects:
        offsets.append(len(pdf_bytes))
        pdf_bytes.extend(obj)
    xref_offset = len(pdf_bytes)
    total_objects = len(objects) + 1
    pdf_bytes.extend(f"xref\n0 {total_objects}\n".encode("utf-8"))
    pdf_bytes.extend(b"0000000000 65535 f \n")
    for offset in offsets[1:]:
        pdf_bytes.extend(f"{offset:010d} 00000 n \n".encode("utf-8"))
    pdf_bytes.extend(
        f"trailer\n<< /Size {total_objects} /Root 1 0 R >>\nstartxref\n{xref_offset}\n%%EOF\n".encode("utf-8")
    )

    with open(output_path, "wb") as pdf_file:
        pdf_file.write(pdf_bytes)


def main() -> None:
    input_path = os.path.join(os.path.dirname(__file__), INPUT_MD)
    output_path = os.path.join(os.path.dirname(__file__), OUTPUT_PDF)
    with open(input_path, "r", encoding="utf-8") as md_file:
        markdown_text = md_file.read()
    lines = markdown_to_lines(markdown_text)
    pages = chunk_lines(lines)
    write_pdf(pages, output_path)


if __name__ == "__main__":
    main()
