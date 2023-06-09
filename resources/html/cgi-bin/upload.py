import os
import cgi

# 멀티파트/form-data 형식의 바디를 파싱하는 함수
def parse_multipart_form_data(body, boundary):
    form_data = {}

    # 각 파트 별로 분리
    parts = body.split("--" + boundary)

    # 파트 개수만큼 반복
    for part in parts:
        if part.strip():  # 빈 줄이 아닌 경우에만 처리
            lines = part.strip().split("\r\n")

            # 헤더 정보 추출
            headers = lines[:-2]
            content_type = headers[0].split(": ")[1]
            name = headers[1].split(": ")[1].strip('"')

            # 파일인 경우에는 파일 데이터 추출
            if "filename" in headers[1]:
                filename = headers[1].split(": ")[2].strip('"')

                # 파일 데이터 추출
                file_data = "\r\n".join(lines[-2:])
                form_data[name] = {
                    "filename": filename,
                    "content_type": content_type,
                    "data": file_data,
                }
            else:  # 일반 필드인 경우에는 값 추출
                value = "\r\n".join(lines[-2:])
                form_data[name] = value

    return form_data


# 클라이언트 요청을 받아 처리하는 함수
def handle_request():
    # 요청 바디 데이터 읽기
    content_length = int(os.environ.get("CONTENT_LENGTH", 0))
    body = os.environ["wsgi.input"].read(content_length).decode("utf-8")

    # Content-Type 헤더에서 멀티파트 경계(boundary) 추출
    content_type = os.environ.get("CONTENT_TYPE", "")
    boundary = content_type.split("boundary=")[-1]

    # 멀티파트/form-data 형식의 바디 파싱
    form_data = parse_multipart_form_data(body, boundary)

    # 파일 저장 처리
    for field_name, field_data in form_data.items():
        if isinstance(field_data, dict):  # 파일 필드인 경우에만 저장
            filename = field_data["filename"]
            file_data = field_data["data"]

            # 파일 저장 경로 설정 (여기에서는 현재 디렉토리에 저장)
            save_path = os.path.join(os.getcwd(), filename)

            # 파일 저장
            with open(save_path, "wb") as file:
                file.write(file_data.encode())

    # 응답 생성
    print("Content-Type: text/plain")
    print()
    print("File upload successful")


# 스크립트를 직접 실행하는 경우에만 처리
if __name__ == "__main__":
    handle_request()