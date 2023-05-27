#include "HttpValidator.hpp"
#include "HttpPage.hpp"

void	HttpValidator::CheckRequestLineSyntax(const HttpRequestLine& requestLine)
{
	// check method
	if (METHODS->find(requestLine.getMethod()) == std::string::npos)
		throw ResponseException(405); // NOT_ALLOWED

	// check http-version
	if (requestLine.getVersion() != HTTP_VERSION)
		throw ResponseException(505); // 505 HTTP Version Not Supported
}

// void	HttpValidator::CheckRequestHeaderSyntax(const HttpRequestHeader& requestHeader)
// {

// }


	// 2. compare port

	// ** index가 autoindex보다 더 높은 우선순위
	// ** 
	// root는 default로 세팅 : webserv의 경로 + resources/html까지의 경로

	// index_page default로 세팅 -> (index.html)
	// error_page default로 세팅 -> (40x.html)
	// error_page default로 세팅 -> (50x.html)

	// 1) 부모의 root가 있다면, _defaultRoot = 부모의 root
	// 2) path = root + location 을 stat -> 경로인가? 파일인가?
	// 2-1) 일치하는거 찾으면, 일단 error_page setting

	// 3-1) 파일인 경우
		// default_root (/user/eunson) + location(/)에 파일이 위치하는가? -> 위치하는 경우 파일 리턴
		// 없을 경우 -> 404 not found
	// 3-2) 경로인 경우
		// index가 있는가? -> o
			// index가 유효한가? -> 보여준다.
			// index가 유효하지 않은가?
				// autoindex가 있는가?
					// autoindex가 유효한가? -> auto-indexing
					// autoindex가 유효하지 않은가? -> 403 forbidden
		// index가 없는 경우 -> 보여준다.

			
	// 4) 에러일 경우
		// location block 내 error_page가 있는가? -> 그거 리턴 (location->get)
		// location block 내 error_page가 없으면 -> serverblock내 error_page(serverblock->get)
			// serverblock내 error_page도 없으면 -> default_error_page
		// 에러페이지가 없는거라면 -> 404

// 	int	command_handler(t_exec_block *exec)
// {
// 	char		**env_lst;
// 	struct stat	path_stat;

// 	env_lst = current_env_lst();
// 	if (stat(exec->command, &path_stat) == 0)
// 	{
// 		if (S_ISDIR(path_stat.st_mode))
// 			print_custom_error(exec->command, 0, IS_DIR);
// 		else if (S_ISREG(path_stat.st_mode))
// 		{
// 			if (execve(exec->command, exec->args, env_lst) == -1)
// 				print_error(exec->command, 0);
// 		}
// 	}
// 	else if (ft_strchr(exec->command, '/'))
// 	{
// 		if (errno == ENOENT)
// 			print_custom_error(exec->command, 0, NO_SUCH_FILE_DIR);
// 		else if (errno == ENOTDIR)
// 			print_custom_error(exec->command, 0, NOT_A_DIR);
// 	}
// 	else
// 		command_execute(exec, env_lst);
// 	return (g_sys.last_exit_status_code);
//}
	//exit(0);
	// root?
	// 2) find location
		// 경로를 못찾으면? 실제 resources 경로에 해당하는 파일이 있는지.
		// autoindex?
		// 둘다 없으면 error-page (여기서 findErrorPage)
		// error-page가 세팅되어 있지 않다면, default-error-page

//(void)config;
// 1) Syntax Check
//HttpValidator::CheckRequestLineSyntax(requestLine);
//HttpValidator::CheckRequestHeaderSyntax(requestHeader);

// 2) find Server
//ServerInfo serverInfo = HttpHandler::findServerInfo(config, requestHeader);

// 3) find Location
//LocationBlock location = HttpHandler::findLocation(serverInfo, requestLine.getRequestURI());

// 4) limit_except Check
//HttpValidator::MethodPermitted(location, method);
	// 메서드가 허용된지 확인하는 로직
	// 허용되지 않으면 예외를 던질 수 있음