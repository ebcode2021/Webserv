# Webserv

## 1. 프로젝트 소개

Webserv는 HTTP/1.1 규격을 준수하는 웹 서버다. 기존 웹 서버와 마찬가지로 클라이언트로부터 HTTP 요청을 받고 응답하는 소프트웨어 프로그램이며, 해당 프로젝트에서는 Nginx를 참고하여 만들었다. \
다중 클라이언트 요청을 단일 스레드에서 처리하기 위해, `kqueue()`를 활용하여 Non-blocking I/O와 Multiplexing 기법을 결합하여 설계하였으며, 동적인 웹 페이지 생성 및 데이터 처리를 위해 CGI(Common Gateway Interface)를 지원한다.

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
            👩🏻‍💻 <a href="https://github.com/ebcode2021"> eunbi son </a>
        </td>
        <td align="center">
            🐼 <a href="https://github.com/minsubro"> minsu kang </a>
        </td>
    </tr>
    <tr>
        <td>역할 분담</td>
        <td>
              - 설정 파일 유효성 검사 <br/>
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

**[소켓 프로세스]**

![socket-flow](https://github.com/ebcode2021/Webserv/assets/84271971/e14a8f9e-2390-4559-8ef8-6bfcaf0bb8c4)

**[HTTP 프로세스]**
![http-flow](https://github.com/ebcode2021/Webserv/assets/84271971/140e2642-4c36-4cc7-aeb6-b493418982f3)

## 7. 주요 기능

### 7-1. Configuration file

**[지시어]**

webserv의 config 파일에서 사용하는 각 지시어들은 Nginx의 config 파일에서 사용하는 지시어들의 동작을 참고하여 만들었다. \
서버에서는 config file에서 사용 가능한 지시어와 해당 지시어의 중복 가능 횟수를 key-value로 설정하여 종류에 따라 각기 다른 파일로 분리하여 보관하고 있다. \
이는 유효성 검사시 해당 지시어가 존재하는지와 중복 가능 여부를 체크하는데 사용된다.

```
limit_except 1
autoindex 65535
client_max_body_size 65535
client_body_temp_path 65535
error_page 65535
index 65535
cgi_pass 1
return 1
root 1
```

<br />

**[프로그램 동작시 필요한 config 파일 예시]**

<img width="980" alt="conf example" src="https://github.com/ebcode2021/Webserv/assets/96279704/dd94e5cc-e1b3-4796-83bb-5e530c627d94">

<br />
<br />

**[지시어 목록]**

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

HTTP는 인터넷을 통해 정보를 송수신하기 위한 프로토콜이다. \
HTTP는 웹 브라우저와 웹 서버간의 통신에 사용되며 요청(request)과 응답(response)로 구성되어 있다. \
클라이언트가 웹 페이지를 통해 HTTP 요청을 서버에 보내면 서버는 요청처리 후 HTTP 응답을 다시 클라이언트에게 전송한다.

<br />

**HTTP 메시지 포멧**

HTTP 메시지 포멧은 아래와 같다.


```
start-line CRLF
headers CRLF

(message-body)
```

<br />

**HTTP 요청**

HTTP 요청은 request-line, headers, body(선택)로 세 부분으로 이루어져 있다.

`request-line : method location HTTP-version`

```
GET /index.html HTTP/1.1
Host: localhost:4242
Cookie: hello=world
```

<br />

**HTTP 응답**

HTTP 응답은 respone-line, headers, body(선택)로 세 부분으로 이루어져 있다.

`response-line : HTTP-version status-code status-reason`

```
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 42

hello!
```

<br />

**HTTP 메서드**

아래는 Webserv에서 지원하는 메서드이다.
| 메서드 | 사용 | Body 여부 |
| :------: | :-----------------: | :-------: |
| `GET` | 데이터 요청 | X |
| `POST` | 데이터를 추가, 작성 | O |
| `DELETE` | 데이터 삭제 | X |

<br />

**HTTP 상태코드**

1xx : Information responses \
2xx : Sucessful responses \
3xx : Redirection messages \
4xx : Client error responses \
5xx : Server error responses

아래는 webserv에서 지원하는 상태코드다.

| status-code |       status-reason        |
| :---------: | :------------------------: |
|     200     |             OK             |
|     201     |          Created           |
|     202     |          Accepted          |
|     204     |         No Content         |
|     301     |     Moved Permanently      |
|     302     |           Found            |
|     304     |        Not Modified        |
|     400     |        Bad Request         |
|     401     |        Unauthorized        |
|     403     |         Forbidden          |
|     404     |         Not Found          |
|     405     |     Method Not Allowed     |
|     413     |  Request Entity Too Large  |
|     500     |   Internal Server Error    |
|     505     | HTTP Version Not Supported |

### 7-3. Session

HTTP는 비연결성 프로토콜로, 이전 요청을 저장하지 않는다. \
그러나 클라이언트 별로 세션을 이용함으로써 이전 요청 상태를 저장하는 방법이 있다.

webserv에서 세션 관리는 서버의 SessionStorage에서 이루어진다. \
SessionStorage는 Session들을 Map 형태로 갖는데, key는 sessionId, value로는 Session을 포함한다.

특정 URL에 대한 클라이언트의 첫 요청에는, 새로운 sessionId를 발급받아 응답 헤더 중 setCookie에 담아 클라이언트에 전송한다. \
이후, 클라이언트 요청 헤더 중 Cookie의 값으로 sessionId가 담겨있고, SessionStorage의 sessionId와 일치하고 유효하다면, 서버는 304 상태코드를 반환하게 된다.

### 7-4. CGI
webserv는 nginx를 참고하여 만든 완전 정적 서버이다. 동적인 페이지를 사용자에게 제공하기 위해서 CGI를 사용한다. \
CGI는 웹 서버와 외부 프로그램 사이의 표준 인터페이스를 정의하는 방법이다. CGI를 사용하면 웹 서버는 사용자의 요청에 따라 외부 프로그램을 실행하고, 그 결과를 웹 브라우저에 돌려줄 수 있다.
CGI는 웹 서버와 프로그램 사이에 데이터를 주고 받을 수 있는 표준화된 프로토콜을 사용한다. 사용자가 웹 페이지에서 양식을 작성하고 제출하면, 웹 서버는 CGI를 통해 해당 양식 데이터를 외불 프로그램을 전달하고, 외부 프로그램은 그 데이터를 처리한 후 결과를 웹 서버에게 반환한다. 웹 서버는 이 결과를 다시 사용자에게 전송하여 화면을 표시한다. \
<br />
CGI는 다음과 같은 프로세스를 따른다.
1. 클라이언트가 웹 페이지에서 양식을 작성하고 제출한다.
2. 웹 서버는 클라이언트의 입력 데이터를 포함한 HTTP 요청을 받는다.
3. 웹 서버는 CGI 프로그램을 실행하고, 클라이언트의 입력 데이터를 CGI 프로그램에 표준입력으로 전달 한다.
4. CGI 프로그램은 입력 데이터를 처리하고, 결과를 웹 서버에게 표준출력으로 반환한다.
5. 웹 서버는 CGI프로그램의 결과를 클라이언트에게 전송한다. 

![CGI_common_gateway_interface svg](https://github.com/ebcode2021/Webserv/assets/96279704/2695ed23-b1c0-4873-bb42-d270de36bed1)

## 8. 참고 자료

**[도서]**

-   [Nginx HTTP 서버:HTTP 서버를 사용한 고성능 웹 서비스 구축](https://www.aladin.co.kr/shop/wproduct.aspx?ItemId=235969450&start=slayer)
-   [모두의 네트워크](https://www.aladin.co.kr/shop/wproduct.aspx?ItemId=151491282)
-   [TCP/IP 소켓 프로그래밍](https://www.aladin.co.kr/shop/wproduct.aspx?ItemId=297117238&start=pgooglemc)

**[공식 문서]**

-   [RFC 7231](https://datatracker.ietf.org/doc/html/rfc7231)
-   [Nginx docs](https://nginx.org/en/docs/http/configuring_https_servers.html)
-   [HTTP status codes](https://developer.mozilla.org/en-US/docs/Web/HTTP/Status)
