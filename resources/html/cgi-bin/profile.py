#!/usr/bin/env python3
import cgi
import os

# 라인 출력
print("HTTP/1.1 200 OK")

# 헤더 출력
print("Content-Type: text/html\n")

# HTML 문서 시작
print("<html>")
print("<head><meta charset=\"UTF-8\"><title>CGI Example</title></head>")
print("<body>")

# 사용자 입력 받기
form = cgi.FieldStorage()
name = form.getvalue("name")
age = form.getvalue("age")
path = os.environ.get('PATH_INFO', '')

# 입력이 제공된 경우에 대한 처리
if name and age:
    print("<p>이름: {}</p>".format(name))
    print("<p>나이: {}</p>".format(age))
else:
    print("<p>이름과 나이를 입력하세요.</p>")

# 입력 세팅
print("<script>")
print("function checkInputs() {")
print("var name = document.getElementsByName('name')[0].value;")
print("var age = document.getElementsByName('age')[0].value;")
print("var submitBtn = document.getElementById('submitBtn');")
print("if (name.trim() === '' || age.trim() === '') {")
print("submitBtn.disabled = true;")
print("} else {")
print("submitBtn.disabled = false;")
print("}")
print("}")
print("</script>")

# 입력 양식 표시
print("<form method='get' action='{}'>".format(path))
print("<label for='name'>이름: </label>")
print("<input type='text' name='name' oninput='checkInputs()'><br><br>")
print("<label for='age'>나이: </label> ")
print("<input type='text' name='age' oninput='checkInputs()'><br><br>")
print("<input type='submit'  id='submitBtn' value='전송' disabled>")
print("</form>")

# HTML 문서 끝
print("</body>")
print("</html>")