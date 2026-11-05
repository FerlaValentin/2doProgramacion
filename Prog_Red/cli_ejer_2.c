#include <stdio.h>
#include <winsock.h>
#include "structs.h"
#pragma comment(lib, "ws2_32.lib")

void printMenu(){
  for(int i = 0; i < 40; ++i) printf("-"); printf("\n");
  puts("1.-) Calculadora.");
  puts("2.-) Usuario.");
  puts("3.-) Latencia");
  for(int i = 0; i < 40; ++i) printf("-"); printf("\n");
}

void askPacketType(int* const type){
  printf("Tipo Paquete: ");
  scanf("%d", type);
  getchar();
}

void calculator(Calculo* const calculation){
  printf("Operando 1: "); scanf("%d", &calculation->num1); getchar();
  printf("Operando 2: "); scanf("%d", &calculation->num2); getchar();
  printf("Operacion: "); scanf("%c", &calculation->operacion); getchar();
}

void user(Usuario* const user){
  printf("Nombre: "); scanf("%49[^\n]", user->nombre);
  printf("Edad: "); scanf("%d", &user->edad); getchar();
  printf("Vida: "); scanf("%d", &user->vida); getchar();
}

void latency(Latencia* const latency){
  LARGE_INTEGER before;
  QueryPerformanceCounter(&before);
  latency->t_cli_envio_ms = before.QuadPart;
}

const char* preparePacket(PKT* const pkt){
  switch(pkt->tipo){
    case 1: calculator(&pkt->Calculo); return "Resultado obtenido: ";
    case 2: user(&pkt->Usuario); return "ID Cliente: ";
    case 3: latency(&pkt->Latencia); return "Latencia ";
    default: return "ERROR";
  };
}

void sendPacket(const SOCKET* const sock, PKT* const pkt){
  send(*sock, (char*)pkt, sizeof(*pkt), 0);
  puts("Enviado...");
}

double calculateLatency(Latencia* const latency){
  LARGE_INTEGER freq, after;

  QueryPerformanceFrequency(&freq);
  QueryPerformanceCounter(&after);
  return (double)(after.QuadPart - latency->t_cli_envio_ms) * 1000 / freq.QuadPart;
}

void printResult(const char* const resultText, PKT* const pkt){
  printf("%s", resultText);
  switch(pkt->tipo){
    case 1: printf("%d\n", pkt->Calculo.res); break;
    case 2: printf("%d\n", pkt->Usuario.id_player); break;
    case 3: printf("%.3f\n", calculateLatency(&pkt->Latencia)); break;
    default: puts("ERROR"); break;
  }
}

void receiveResult(const char* const resultText, const SOCKET* const sock, PKT* const pkt){
  recv(*sock, (char*)pkt, sizeof(*pkt), 0);
  printResult(resultText, pkt);
}

int main(){
  WSADATA wsa;
  SOCKET sock;
  struct sockaddr_in ip;
  PKT pkt;

  WSAStartup(MAKEWORD(2,0), &wsa);
  sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  ip.sin_family = AF_INET;
  ip.sin_addr.s_addr = inet_addr("127.0.0.1");
  ip.sin_port = htons(7979);

  connect(sock, (SOCKADDR*)&ip, sizeof(ip));
  while(1){
    memset(&pkt, 0, sizeof(pkt));
    printMenu();
    askPacketType(&pkt.tipo);
    const char* resultText = preparePacket(&pkt);
    sendPacket(&sock, &pkt);
    receiveResult(resultText, &sock, &pkt);
  }
}