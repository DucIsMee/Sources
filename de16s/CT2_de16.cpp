// De16 - CT2 (server) - Windows (Winsock)
// Receives n and array, exits when n<=0, prints received array in reverse order (client already reversed)
// Compile (MinGW): g++ CT2_de16.cpp -o CT2_de16 -lws2_32

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>

using namespace std;

bool recv_all(SOCKET s, char* buf, int len){
    int total=0;
    while(total<len){
        int r = recv(s, buf+total, len-total, 0);
        if(r==0) return false; if(r==SOCKET_ERROR) return false;
        total+=r;
    }
    return true;
}

int main(){
    WSADATA wsa; WSAStartup(MAKEWORD(2,2), &wsa);
    SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in addr{}; addr.sin_family=AF_INET; addr.sin_port=htons(5000); addr.sin_addr.s_addr=INADDR_ANY;
    bind(listen_sock,(sockaddr*)&addr,sizeof(addr));
    listen(listen_sock,1);
    cout<<"Server listening on 127.0.0.1:5000\n";
    SOCKET client = accept(listen_sock,nullptr,nullptr);
    cout<<"Client connected\n";
    while(true){
        int32_t nn;
        if(!recv_all(client,(char*)&nn,sizeof(nn))){ cout<<"connection closed\n"; break; }
        int n = ntohl(nn);
        if(n<=0){ cout<<"Received n<=0, exiting loop\n"; break; }
        vector<int32_t> a(n);
        for(int i=0;i<n;++i){ int32_t v; if(!recv_all(client,(char*)&v,sizeof(v))){ cout<<"recv failed\n"; goto DONE; } a[i]=ntohl(v); }
        cout<<"Received array (from client, sent reversed): ";
        for(int i=0;i<n;++i) cout<<a[i]<<" "; cout<<"\n";
    }
DONE:
    closesocket(client); closesocket(listen_sock); WSACleanup();
    return 0;
}
