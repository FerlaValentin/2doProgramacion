#include <stdio.h>
#include <winsock.h>
#include "structs.h"
#pragma comment(lib, "ws2_32.lib")

void calculate(Calculo* const calculations){
  switch(calculations->operacion){
    case '+': calculations->res = calculations->num1 + calculations->num2; break;
    case '-': calculations->res = calculations->num1 - calculations->num2; break;
    case '*': calculations->res = calculations->num1 * calculations->num2; break;
    case '/': calculations->res = calculations->num1 / calculations->num2; break;
    default: puts("ERROR"); break;
  }
}

void assignID(int* const user_id){
  static int last_assigned_id = 0;
  *user_id = ++last_assigned_id;
}

void processPacket(PKT* const pkt){
  switch(pkt->tipo){
    case 1: calculate(&pkt->Calculo); break;
    case 2: assignID(&pkt->Usuario.id_player); break;
    case 3: break;
    default: puts("ERROR"); break;
  }
}

int main(){
  WSADATA wsa;
  SOCKET sock, sock_c;
  struct sockaddr_in ip;
  PKT pkt;

  WSAStartup(MAKEWORD(2,0), &wsa);
  sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  ip.sin_family = AF_INET;
  ip.sin_addr.s_addr = inet_addr("0.0.0.0");
  ip.sin_port = htons(7979);

  bind(sock, (SOCKADDR*)&ip, sizeof(ip));
  listen(sock, SOMAXCONN);

  sock_c = accept(sock, NULL, NULL);
  while(1){
    memset(&pkt, 0, sizeof(pkt));
    recv(sock_c, (char*)&pkt, sizeof(pkt), 0);
    processPacket(&pkt);
    send(sock_c, (char*)&pkt, sizeof(pkt), 0);
  }
}