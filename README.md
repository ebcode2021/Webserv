# Webserv

## 1. 프로젝트 소개

> 이 프로젝트는 Nginx를 참고하여 HTTP/1.1 규격을 준수하는 웹서버를 C++98 환경에서 개발하였다.\
> 다중 클라이언트 요청을 단일 스레드에서 처리하기 위해, kqueue()를 활용하여 Non-blocking I/O와 Multiplexing 기법을 결합하였으며 CGI(Common Gateway Interface)를 지원하여 동적인 웹 페이지 생성 및 데이터 처리가 가능하다.

---

## 2. 개발 기간

23.04 - 23.07

---

## 3. 개발 환경

C++ 98

---

## 4. 멤버구성

<table>
  <tr>
    <td align="center">
        <a href="https://github.com/ebcode2021">
            <img src="https://avatars.githubusercontent.com/u/84271971?v=4" width="100px;"/>
            <br />
            <sub>
                <b>Eunbi Son</b>
            </sub>
        </a>
        <br />
    <td align="center">
        <a href="https://github.com/minsubro">
            <img src="https://avatars.githubusercontent.com/u/96279704?v=4" width="100px;" />
            <br /> 
            <sub>
                <b>Minsu Kang</b>
            </sub>
        </a>
        <br />
    </td>
  </tr>
</table>

: 설정 파일 파싱, 소켓 이벤트 처리 \
: HTTP 파싱, HTTP 메시지 처리

---

## 5. 사용법

```
make
./webserv [설정 파일.conf]
```

---

## 6. flow chart

CGI 제외했다고 설명 쓰기
![Blank board](https://github.com/ebcode2021/Webserv/assets/84271971/e14a8f9e-2390-4559-8ef8-6bfcaf0bb8c4)

---

## 7. 주요 기능

### 7-1. Configuration file
webserv의 config 파일에서 사용하는 각 지시어 들은 Nginx의 config애서 사용하는 지시어들의 동작을 참고하여 만들었다.<br/>
프로그램 동작시 필요한 conf파일 예시
<img width="980" alt="Screen Shot 2024-01-22 at 5 33 56 PM" src="https://github.com/ebcode2021/Webserv/assets/96279704/dd94e5cc-e1b3-4796-83bb-5e530c627d94">
```
지시어 목록

server                  : 하나의 호스트를 선언하는데 사용
location                : 특정 URL 처리 방법 지정
error_page              : 오류 발생시 사용자에게 보여줄 페이지를 지정하는데 사용
client_max_body_size    : 클라이언트가 전송하는 본문(body)의 크기(MB)를 제한하는데 사용
client_body_temp_path   : 클라이언트가 업로드한 데이터를 저장하는 임시 디렉터리의 경로를 설정하는 데 사용
autoindex               : 디렉터리 색인 기능을 활성화 또는 비활성화 하는데 사용
index                   : 디렉터리에 접근했을 때 표시할 기본 문서를 지정하는데 사용
return                  : 클라이언트에게 보낼 응답을 지정하는데 사용(webserv에서는 리디렉션 용도로 사용)
cgi_pass                : CGI 프로그램을 실행할 때 사용되는 지시어
root                    : 정적 파일의 기본 경로를 지정하는데 사용
```
### 7-2. HTTP Message

### 7-3. CGI
웹 서버에서 동적인 페이지를 보여 주기 위해 임의의 프로그램을 실행할 수 있도록 하는 기술 중 하나이다. \
webserv는 nginx를 참고하여 만들었으므로 완전 정적 서버이다. 동적인 페이지를 제공하기 위해여 CGI를 지원한다. \
요청받은 페이지를 외부 스크립트를 이용해 동적으로 생성하여 보내주는 기능이다. 여러 스크립트를 이용할 수 있지만 webserv에서는 python 스크립트만을 지원한다.
![CGI_common_gateway_interface svg](https://github.com/ebcode2021/Webserv/assets/96279704/2695ed23-b1c0-4873-bb42-d270de36bed1)


---
## 8. 참고 자료

-   Nginx HTTP 서버:HTTP 서버를 사용한 고성능 웹 서비스 구축
-   모두의 네트워크
-   TCP/IP 소켓 프로그래밍

-   RFC 문서
-   Nginx 공식문서
