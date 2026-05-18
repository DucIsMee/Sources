// De18 - CT2 (server) - Windows (Winsock)
// Receives n and array; if n<3 exit; else display first 3 smallest values in ascending order
// Compile: g++ CT2_de18.cpp -o CT2_de18 -lws2_32

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool recv_all(SOCKET s, char* buf, int len){ int total=0; while(total<len){ int r=recv(s,buf+total,len-total,0); if(r<=0) return false; total+=r; } return true; }

int main(){ WSADATA w; WSAStartup(MAKEWORD(2,2),&w);
    SOCKET listen_sock=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in addr{}; addr.sin_family=AF_INET; addr.sin_port=htons(5000); addr.sin_addr.s_addr=INADDR_ANY;
    bind(listen_sock,(sockaddr*)&addr,sizeof(addr)); listen(listen_sock,1);
    cout<<"Server listening 127.0.0.1:5000\n";
    SOCKET client=accept(listen_sock,nullptr,nullptr);
    cout<<"Client connected\n";
    while(true){ int32_t nn; if(!recv_all(client,(char*)&nn,sizeof(nn))){ cout<<"conn closed\n"; break; } int n=ntohl(nn); if(n<3){ cout<<"n<3 received, exiting\n"; break; } vector<int> a(n); for(int i=0;i<n;++i){ int32_t v; if(!recv_all(client,(char*)&v,sizeof(v))){ cout<<"recv failed\n"; goto DONE; } a[i]=ntohl(v); }
        sort(a.begin(), a.end()); cout<<"Three smallest: "; for(int i=0;i<3;++i) cout<<a[i]<<" "; cout<<"\n";
    }
DONE:
    closesocket(client); closesocket(listen_sock); WSACleanup(); return 0; }
