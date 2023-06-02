#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

bool checkIpAddressMatch(const char* clientIpAddress, const char* allowedIpAddress) {
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return false;
    }

    struct sockaddr_in clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = inet_addr(clientIpAddress);
    clientAddr.sin_port = htons(0);  // Use any available port

    if (bind(clientSocket, (struct sockaddr*)&clientAddr, sizeof(clientAddr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(clientSocket);
        return false;
    }

    struct sockaddr_in name;
    socklen_t nameLength = sizeof(name);
    if (getsockname(clientSocket, (struct sockaddr*)&name, &nameLength) < 0) {
        std::cerr << "Failed to get socket name" << std::endl;
        close(clientSocket);
        return false;
    }

    char resolvedIpAddress[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &(name.sin_addr), resolvedIpAddress, INET_ADDRSTRLEN) == NULL) {
        std::cerr << "Failed to convert IP address to string" << std::endl;
        close(clientSocket);
        return false;
    }

    close(clientSocket);

    if (strcmp(resolvedIpAddress, allowedIpAddress) == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    const char* clientIpAddress = "클라이언트 IP 주소를 여기에 입력하세요";
    const char* allowedIpAddress = "제한된 IP 주소를 여기에 입력하세요";

    if (checkIpAddressMatch(clientIpAddress, allowedIpAddress)) {
        std::cout << "IP 주소가 일치합니다." << std::endl;
    } else {
        std::cout << "IP 주소가 일치하지 않습니다." << std::endl;
    }

    return 0;
}
