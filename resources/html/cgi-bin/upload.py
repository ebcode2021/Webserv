#!/usr/bin/env python
import cgi
import os

# CGI 환경 변수 설정
print("cgi 스크립트 시작")
UPLOAD_DIR = '/Users/minsu/Desktop/42seoul/webserv/resources/upload/'  # 파일을 저장할 디렉토리 설정

# 폼 데이터 가져오기
form = cgi.FieldStorage()

print("cgi 스크립트 끝")

# print(form)

# 업로드된 파일 처리
if 'file' in form:
    fileitem = form['file']

    # 파일 경로와 이름 설정
    filename = os.path.basename(fileitem.filename)
    filepath = os.path.join(UPLOAD_DIR, filename)

    # 파일 저장
    with open(filepath, 'wb') as f:
        f.write(fileitem.file.read())

    print("Content-Type: text/html")
    print()
    print("<h1>파일 업로드 완료</h1>")
    print("<p>업로드된 파일: {}</p>".format(filename))
else:
    print("Content-Type: text/html")
    print()
    print("<h1>파일을 선택하세요.</h1>")
