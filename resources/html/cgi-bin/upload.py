#!/usr/bin/env python
import cgi
import os

# CGI 환경 변수 설정
UPLOAD_DIR = os.getenv("PATH_INFO")


# 폼 데이터 가져오기
form = cgi.FieldStorage()
# 업로드된 파일 처리
if 'file' in form:
    fileitem = form['file']

    # 파일 경로와 이름 설정
    filename = os.path.basename(fileitem.filename)
    filepath = os.path.join(UPLOAD_DIR, filename)

    os.makedirs(os.path.dirname(filepath), exist_ok=True)

    # 파일 저장
    with open(filepath, 'wb') as f:
        f.write(fileitem.file.read())

    print("HTTP/1.1 201 Created")

# 헤더 출력
    print("Content-Type: text/html\n")
# HTML 문서 시작
    print("<html>")
    print("<head><meta charset=\"UTF-8\"><title>CGI Example</title></head>")
    print("<body>")
    print("<h1>파일 업로드 완료</h1>")
    print("<p>업로드된 파일: {}</p>".format(filename))
    print("</body>")
