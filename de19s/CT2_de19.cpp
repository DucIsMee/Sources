// De19 - CT2 (server) - Windows (Winsock)
// Receives k values; if k>1042021 exit; otherwise print hex of current maximum seen
// Compile: g++ CT2_de19.cpp -o CT2_de19 -lws2_32

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <limits>

using namespace std;

bool recv_all(SOCKET s, char* buf, int len){ int total=0; while(total<len){ int r=recv(s,buf+total,len-total,0); if(r<=0) return false; total+=r; } return true; }

int main(){ WSADATA w; WSAStartup(MAKEWORD(2,2),&w);
    SOCKET listen_sock=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in addr{}; addr.sin_family=AF_INET; addr.sin_port=htons(5000); addr.sin_addr.s_addr=INADDR_ANY;
    bind(listen_sock,(sockaddr*)&addr,sizeof(addr)); listen(listen_sock,1);
    cout<<"Server listening 127.0.0.1:5000\n";
    SOCKET client=accept(listen_sock,nullptr,nullptr);
    cout<<"Client connected\n";
    int current_max = numeric_limits<int>::min();
    while(true){ int32_t kk; if(!recv_all(client,(char*)&kk,sizeof(kk))){ cout<<"conn closed\n"; break; } int k = ntohl(kk);
        if(k>1042021){ cout<<"k>1042021 received, exiting\n"; break; }
        if(k>current_max) current_max = k;
        printf("Current max hex: 0x%X\n", current_max);
    }
    closesocket(client); closesocket(listen_sock); WSACleanup(); return 0; }
