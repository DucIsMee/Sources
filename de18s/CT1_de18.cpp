// De18 - CT1 (client) - Windows (Winsock)
// Sends n (must be >=3) and array to server; if n<3 sends termination signal
// Compile: g++ CT1_de18.cpp -o CT1_de18 -lws2_32

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>

using namespace std;

bool send_all(SOCKET s, const char* buf, int len){ int total=0; while(total<len){ int sent=send(s,buf+total,len-total,0); if(sent==SOCKET_ERROR) return false; total+=sent;} return true; }

int main(){ WSADATA w; WSAStartup(MAKEWORD(2,2),&w);
    SOCKET sock=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in srv{}; srv.sin_family=AF_INET; srv.sin_port=htons(5000); inet_pton(AF_INET,"127.0.0.1",&srv.sin_addr);
    if(connect(sock,(sockaddr*)&srv,sizeof(srv))==SOCKET_ERROR){ cerr<<"connect failed\n"; WSACleanup(); return 1; }
    while(true){ cout<<"Enter n (>=3, else quit): "; int n; if(!(cin>>n)) break; int32_t nn=htonl(n); if(!send_all(sock,(char*)&nn,sizeof(nn))){ cerr<<"send failed\n"; break; } if(n<3) break; vector<int32_t> a(n); for(int i=0;i<n;++i){ cout<<"a["<<i<<"]="; cin>>a[i]; }
        for(int i=0;i<n;++i){ int32_t v=htonl(a[i]); if(!send_all(sock,(char*)&v,sizeof(v))){ cerr<<"send failed\n"; goto DONE; } }
    }
DONE:
    closesocket(sock); WSACleanup(); return 0; }
