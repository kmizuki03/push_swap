#!/usr/bin/env python3
"""
Convert Markdown to PDF with Japanese support
"""

import markdown
from weasyprint import HTML, CSS
from weasyprint.text.fonts import FontConfiguration

def markdown_to_pdf(md_file, pdf_file):
    """Convert markdown file to PDF with Japanese font support"""

    # Read markdown file
    with open(md_file, 'r', encoding='utf-8') as f:
        md_content = f.read()

    # Convert markdown to HTML
    html_content = markdown.markdown(
        md_content,
        extensions=[
            'markdown.extensions.tables',
            'markdown.extensions.fenced_code',
            'markdown.extensions.codehilite',
            'markdown.extensions.toc'
        ]
    )

    # Create complete HTML document with Japanese font support
    html_doc = f"""
    <!DOCTYPE html>
    <html lang="ja">
    <head>
        <meta charset="UTF-8">
        <title>push_swap コードレビュー</title>
        <style>
            @page {{
                size: A4;
                margin: 2cm;
                @top-right {{
                    content: counter(page);
                    font-family: sans-serif;
                }}
            }}

            body {{
                font-family: "DejaVu Sans", "Noto Sans CJK JP", sans-serif;
                line-height: 1.6;
                color: #333;
                font-size: 11pt;
            }}

            h1 {{
                color: #2c3e50;
                border-bottom: 3px solid #3498db;
                padding-bottom: 10px;
                page-break-before: always;
                margin-top: 0;
            }}

            h1:first-of-type {{
                page-break-before: auto;
            }}

            h2 {{
                color: #34495e;
                border-bottom: 2px solid #95a5a6;
                padding-bottom: 5px;
                margin-top: 30px;
            }}

            h3 {{
                color: #555;
                margin-top: 25px;
            }}

            h4 {{
                color: #666;
                margin-top: 20px;
            }}

            code {{
                background-color: #f4f4f4;
                padding: 2px 6px;
                border-radius: 3px;
                font-family: "DejaVu Sans Mono", "Courier New", monospace;
                font-size: 0.9em;
                color: #d14;
            }}

            pre {{
                background-color: #f8f8f8;
                border: 1px solid #ddd;
                border-left: 4px solid #3498db;
                padding: 15px;
                overflow-x: auto;
                border-radius: 4px;
                line-height: 1.4;
            }}

            pre code {{
                background-color: transparent;
                padding: 0;
                color: #333;
                font-size: 10pt;
            }}

            table {{
                border-collapse: collapse;
                width: 100%;
                margin: 20px 0;
                font-size: 10pt;
            }}

            th, td {{
                border: 1px solid #ddd;
                padding: 10px;
                text-align: left;
            }}

            th {{
                background-color: #3498db;
                color: white;
                font-weight: bold;
            }}

            tr:nth-child(even) {{
                background-color: #f9f9f9;
            }}

            blockquote {{
                border-left: 4px solid #e74c3c;
                padding-left: 15px;
                margin-left: 0;
                color: #555;
                font-style: italic;
            }}

            ul, ol {{
                margin: 15px 0;
                padding-left: 30px;
            }}

            li {{
                margin: 8px 0;
            }}

            a {{
                color: #3498db;
                text-decoration: none;
            }}

            hr {{
                border: none;
                border-top: 2px solid #ecf0f1;
                margin: 30px 0;
            }}

            .page-break {{
                page-break-after: always;
            }}
        </style>
    </head>
    <body>
        {html_content}
    </body>
    </html>
    """

    # Configure font
    font_config = FontConfiguration()

    # Convert HTML to PDF
    HTML(string=html_doc).write_pdf(
        pdf_file,
        font_config=font_config
    )

    print(f"PDF generated successfully: {pdf_file}")

if __name__ == "__main__":
    markdown_to_pdf(
        "/home/user/push_swap/code_review.md",
        "/home/user/push_swap/code_review.pdf"
    )
