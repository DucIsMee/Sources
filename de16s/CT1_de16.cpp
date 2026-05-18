// De16 - CT1 (client) - Windows (Winsock)
// Sends n and array in reverse order to server at 127.0.0.1:5000
// Compile (MinGW): g++ CT1_de16.cpp -o CT1_de16 -lws2_32

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>

using namespace std;

bool send_all(SOCKET s, const char* buf, int len){
    int total=0;
    while(total<len){
        int sent = send(s, buf+total, len-total, 0);
        if(sent==SOCKET_ERROR) return false;
        total+=sent;
    }
    return true;
}

int main(){
    WSADATA wsa; WSAStartup(MAKEWORD(2,2), &wsa);
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in srv{}; srv.sin_family=AF_INET; srv.sin_port=htons(5000);
    inet_pton(AF_INET, "127.0.0.1", &srv.sin_addr);
    if(connect(sock, (sockaddr*)&srv, sizeof(srv))==SOCKET_ERROR){
        cerr<<"Connect failed\n"; WSACleanup(); return 1;
    }

    while(true){
        cout<<"Enter n (<=0 to quit): "; int n; if(!(cin>>n)) break;
        if(n<=0){
            int32_t nn=htonl(n);
            send_all(sock, (char*)&nn, sizeof(nn));
            break;
        }
        vector<int32_t> a(n);
        for(int i=0;i<n;++i){ cout<<"a["<<i<<"]="; cin>>a[i]; }
        // send n
        int32_t nn = htonl(n);
        if(!send_all(sock,(char*)&nn,sizeof(nn))){ cerr<<"send failed\n"; break; }
        // send reversed array
        for(int i=n-1;i>=0;--i){ int32_t v = htonl(a[i]); if(!send_all(sock,(char*)&v,sizeof(v))){ cerr<<"send failed\n"; goto DONE; } }
    }
DONE:
    closesocket(sock); WSACleanup();
    return 0;
}
