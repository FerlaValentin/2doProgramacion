#include <stdio.h>

#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

int main(){
    WSADATA wsa;
    SOCKET sock, sock_c;
    struct sockaddr_in ip;
    char buffer[50];
    int bytes=0;

    WSAStartup(MAKEWORD(2,0), &wsa);//PRIMERA FUNCION QUE SE TIENE QUE LLAMAR
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    ip.sin_family = AF_INET;
    ip.sin_port = htons(7777);
    ip.sin_addr.S_un.S_addr = inet_addr("0.0.0.0");
    bind(sock, (SOCKADDR*)&ip, sizeof(ip));
    listen(sock, SOMAXCONN);
    sock_c = accept(sock, NULL,NULL);//!BLOQUEANTE
    
    return 0;
}