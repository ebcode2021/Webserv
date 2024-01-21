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
webserv config 파일에서 사용하는 각 지시어 들은 Nginx의 config 파일을 참고하였다.

### 7-2. HTTP Message

### 7-3. CGI

---

## 8. 참고 자료

-   Nginx HTTP 서버:HTTP 서버를 사용한 고성능 웹 서비스 구축
-   모두의 네트워크
-   TCP/IP 소켓 프로그래밍

-   RFC 문서
-   Nginx 공식문서
