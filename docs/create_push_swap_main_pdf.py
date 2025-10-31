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
LINE_HEIGHT = 14
MAX_LINES_PER_PAGE = int((TOP_MARGIN - BOTTOM_MARGIN) / LINE_HEIGHT) + 1
FONT_RESOURCE_NAME = "F1"
FONT_BASE_NAME = "HeiseiKakuGo-W5"
ENCODING = "shift_jis"


def markdown_to_lines(markdown_text: str) -> List[str]:
    lines: List[str] = []
    for raw_line in markdown_text.splitlines():
        line = raw_line.strip()
        if not line:
            lines.append("")
            continue
        if line.startswith("#"):
            level = len(line) - len(line.lstrip("#"))
            heading = line[level:].strip().replace("`", "")
            lines.append(heading.upper())
            continue
        bullet = ""
        if line.startswith(("- ", "* ")):
            bullet = "・"
            line = line[2:].strip()
        elif any(line.startswith(f"{n}. ") for n in range(1, 10)):
            bullet = "・"
            line = line[line.find(" ") + 1 :].strip()
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


def encode_line_for_pdf(text: str) -> str:
    encoded = text.encode(ENCODING, errors="replace")
    return encoded.hex().upper()


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
    content_lines = [
        "BT",
        f"/{FONT_RESOURCE_NAME} {FONT_SIZE} Tf",
        f"1 0 0 1 {LEFT_MARGIN} {TOP_MARGIN} Tm",
        f"{LINE_HEIGHT} TL",
    ]
    first = True
    for line in lines:
        text_hex = encode_line_for_pdf(line)
        if first:
            content_lines.append(f"<{text_hex}> Tj")
            first = False
        else:
            content_lines.append("T*")
            content_lines.append(f"<{text_hex}> Tj")
    content_lines.append("ET")
    content = "\n".join(content_lines)
    return content.encode("utf-8")


def write_pdf(pages: List[List[str]], output_path: str) -> None:
    objects: List[bytes] = []
    n_pages = len(pages)
    font_type0_obj_number = 3 + 2 * n_pages
    cid_font_obj_number = font_type0_obj_number + 1
    font_descriptor_obj_number = font_type0_obj_number + 2

    page_objects: List[bytes] = []
    content_objects: List[bytes] = []
    for page_index, lines in enumerate(pages):
        content_stream = build_content_stream(lines)
        content_obj_number = 3 + n_pages + page_index
        content_obj = (
            f"{content_obj_number} 0 obj\n".encode("utf-8")
            + f"<< /Length {len(content_stream)} >>\n".encode("utf-8")
            + b"stream\n"
            + content_stream
            + b"\nendstream\nendobj\n"
        )
        content_objects.append(content_obj)

        page_obj_number = 3 + page_index
        page_obj = (
            f"{page_obj_number} 0 obj\n".encode("utf-8")
            + b"<< /Type /Page /Parent 2 0 R "
            + f"/MediaBox [0 0 {PAGE_WIDTH} {PAGE_HEIGHT}] ".encode("utf-8")
            + f"/Contents {content_obj_number} 0 R ".encode("utf-8")
            + f"/Resources << /Font << /{FONT_RESOURCE_NAME} {font_type0_obj_number} 0 R >> >> >>\nendobj\n".encode("utf-8")
        )
        page_objects.append(page_obj)

    pages_kids = "[ " + " ".join(f"{3 + i} 0 R" for i in range(n_pages)) + " ]"
    pages_obj = (
        f"2 0 obj\n<< /Type /Pages /Count {n_pages} /Kids {pages_kids} >>\nendobj\n".encode("utf-8")
    )

    catalog_obj = b"1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"

    font_type0_obj = (
        f"{font_type0_obj_number} 0 obj\n".encode("utf-8")
        + b"<< /Type /Font /Subtype /Type0 "
        + f"/BaseFont /{FONT_BASE_NAME} ".encode("utf-8")
        + b"/Encoding /90ms-RKSJ-H "
        + f"/DescendantFonts [{cid_font_obj_number} 0 R] >>\nendobj\n".encode("utf-8")
    )

    cid_font_obj = (
        f"{cid_font_obj_number} 0 obj\n".encode("utf-8")
        + b"<< /Type /Font /Subtype /CIDFontType0 "
        + f"/BaseFont /{FONT_BASE_NAME} ".encode("utf-8")
        + b"/CIDSystemInfo << /Registry (Adobe) /Ordering (Japan1) /Supplement 2 >> "
        + f"/FontDescriptor {font_descriptor_obj_number} 0 R ".encode("utf-8")
        + b"/DW 1000 >>\nendobj\n"
    )

    font_descriptor_obj = (
        f"{font_descriptor_obj_number} 0 obj\n".encode("utf-8")
        + b"<< /Type /FontDescriptor "
        + f"/FontName /{FONT_BASE_NAME} ".encode("utf-8")
        + b"/Flags 4 /Ascent 880 /Descent -120 /CapHeight 880 /ItalicAngle 0 "
        + b"/StemV 120 /FontBBox [-170 -254 1000 880] >>\nendobj\n"
    )

    objects.append(catalog_obj)
    objects.append(pages_obj)
    objects.extend(page_objects)
    objects.extend(content_objects)
    objects.append(font_type0_obj)
    objects.append(cid_font_obj)
    objects.append(font_descriptor_obj)

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
