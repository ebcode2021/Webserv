# Webserv

## 1. 프로젝트 소개

> Webserv는 Nginx를 참고하여 HTTP/1.1 규격을 준수하는 웹 서버다.\
> 다중 클라이언트 요청을 단일 스레드에서 처리하기 위해, kqueue()를 활용하여 Non-blocking I/O와 Multiplexing 기법을 결합하였으며 CGI(Common Gateway Interface)를 지원하여 동적인 웹 페이지 생성 및 데이터 처리가 가능하다.

## 2. 개발 기간

23.04 - 23.07

## 3. 개발 환경

C++ 98

## 4. 멤버구성

<table align="center">
    <tr>
        <td />
        <td align="center">
            <a href="https://github.com/ebcode2021">
                <img src="https://avatars.githubusercontent.com/u/84271971?v=4" width="100" />
            </a>
        </td>
        <td align="center">
            <a href="https://github.com/minsubro">
                <img src="https://avatars.githubusercontent.com/u/96279704?v=4" width="100" />
            </a>
        </td>
    </tr>
    <tr>
        <td />
        <td align="center">
            <a href="https://github.com/guune">👩🏻‍💻 eunbi son</a>
        </td>
        <td align="center">
            <a href="https://github.com/minsubro">🐼 minsu kang</a>
        </td>
    </tr>
    <tr>
        <td>역할 분담</td>
        <td>
              - 설정 파일 유효성 검사 <br/>
              - HTTP 요청 파싱 <br />
              - HTTP 메시지 처리
        </td>
        <td>
              - 설정 파일 파싱 <br />
              - kqeue() 를 활용한 소켓 이벤트 처리
        </td>
    </tr>
</table>

## 5. 사용법

```
make
./webserv [설정 파일.conf]
```

## 6. flow chart

구현한 webserv의 프로세스는 아래와 같다.(CGI는 포함 X)

![Blank board](https://github.com/ebcode2021/Webserv/assets/84271971/e14a8f9e-2390-4559-8ef8-6bfcaf0bb8c4)

## 7. 주요 기능

### 7-1. Configuration file

webserv의 config 파일에서 사용하는 각 지시어 들은 Nginx의 config애서 사용하는 지시어들의 동작을 참고하여 만들었다.<br/>

[프로그램 동작시 필요한 conf파일 예시]

<img width="980" alt="conf example" src="https://github.com/ebcode2021/Webserv/assets/96279704/dd94e5cc-e1b3-4796-83bb-5e530c627d94">

<br />
[지시어 목록]

```
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

ㄹㅇㄹ

### 7-3. CGI
### 1
webserv는 nginx를 참고하여 만든 완전 정적 서버이다. 동적인 페이지를 사용자에게 제공하기 위해서 CGI를 사용한다. \
CGI는 웹 서버에서 동적인 페이지를 보여 주기 위해 요청받은 페이지를 외부 스크립트를 이용해 동적으로 생성할때 외부 스크립트에 요청의 정보를 넘겨주는 표준이다. 여러 스크립트를 이용할 수 있지만 webserv에서는 python 스크립트만을 지원한다. \
클라이언트에서 요청을 받으면 요청받은 리소스가 cgi 프로그램에 대응되는 지 확인하고 cgi 프로그램에 요청에 대한 정보를 표준 입력으로 전달해준다. \
cgi가 생성한 리소스를 표준출력으로 서버에 전달하면 서버는 그 리소스를 그대로 클라이언트에 전달해준다. 이렇게 동적인 페이지를 생성할 수 있다. \
### 2
CGI는 웹 서버와 외부 프로그램 사이의 표준 인터페이스를 정의하는 방법이다. CGI를 사용하면 웹 서버는 사용자의 요청에 따라 외부 프로그램을 실행하고, 그 결과를 웹 브라우저에 돌려줄 수 있다.
CGI는 웹 서버와 프로그램 사이에 데이터를 주고 받을 수 있는 표준화된 프로토콜을 사용한다. 사용자가 웹 페이지에서 양식을 작성하고 제출하면, 웹 서버는 CGI를 통해 해당 양식 데이터를 외불 프로그램을 전달하고, 외부 프로그램은 그 데이터를 처리한 후 결과를 웹 서버에게 반환한다. 웹 서버는 이 결과를 다시 사용자에게 전송하여 화면을 표시한다. \
CGI는 다음과 같은 프로세스를 따른다.
1. 클라이언트가 웹 페이지에서 양식을 작성하고 제출한다.
2. 웹 서버는 클라이언트의 입력 데이터를 포함한 HTTP 요청을 받는다.
3. 웹 서버는 CGI 프로그램을 실행하고, 클라이언트의 입력 데이터를 CGI 프로그램에 표준입력으로 전달 한다.
4. CGI 프로그램은 입력 데이터를 처리하고, 결과를 웹 서버에게 표준출력으로 반환한다.
5. 웹 서버는 CGI프로그램의 결과를 클라이언트에게 전송한다. 

![CGI_common_gateway_interface svg](https://github.com/ebcode2021/Webserv/assets/96279704/2695ed23-b1c0-4873-bb42-d270de36bed1)

## 8. 참고 자료

-   Nginx HTTP 서버:HTTP 서버를 사용한 고성능 웹 서비스 구축
-   모두의 네트워크
-   TCP/IP 소켓 프로그래밍

-   RFC 문서
-   Nginx 공식문서
