// De19 - CT1 (client) - Windows (Winsock)
// Generates random ints k until k>1042021; sends each k to server
// Compile: g++ CT1_de19.cpp -o CT1_de19 -lws2_32

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <random>
#include <chrono>

using namespace std;

bool send_all(SOCKET s, const char* buf, int len){ int total=0; while(total<len){ int sent=send(s,buf+total,len-total,0); if(sent==SOCKET_ERROR) return false; total+=sent; } return true; }

int main(){ WSADATA w; WSAStartup(MAKEWORD(2,2),&w);
    SOCKET sock=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in srv{}; srv.sin_family=AF_INET; srv.sin_port=htons(5000); inet_pton(AF_INET,"127.0.0.1",&srv.sin_addr);
    if(connect(sock,(sockaddr*)&srv,sizeof(srv))==SOCKET_ERROR){ cerr<<"connect failed\n"; WSACleanup(); return 1; }
    std::mt19937 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());
    while(true){ int k = int(rng()); cout<<"Generated k="<<k<<"\n"; int32_t kk=htonl(k); if(!send_all(sock,(char*)&kk,sizeof(kk))){ cerr<<"send failed\n"; break; } if(k>1042021) break; }
    closesocket(sock); WSACleanup(); return 0; }
