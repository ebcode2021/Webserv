#include "webserv.hpp"
#include "Config.hpp"


int main(int argc, char *argv[])
{
	if (Config::fileCheck(argc, argv))
	{
		Config config(argv[1]);
		std::cout << "컨피그 저장 완료" << std::endl;
		//config.printServerList();
		// 통신 시작
		// 저장된거 이용해서 소켓 열기 ()
		
		//SocketData socketData;
		//socketData.Connection(config);	
	}
	return 0;
}
