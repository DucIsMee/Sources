#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
bool send_all(int s,const char*buf,int len){int t=0;while(t<len){int r=send(s,buf+t,len-t,0); if(r<=0) return false; t+=r;} return true;}
int main(){
    int s=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in srv{AF_INET,htons(5000),{0}}; inet_pton(AF_INET,"127.0.0.1",&srv.sin_addr);
    if(connect(s,(sockaddr*)&srv,sizeof(srv))<0) return 1;
    mt19937 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());
    while(true){ int k=(int)rng(); int32_t kk=htonl(k); if(!send_all(s,(char*)&kk,sizeof(kk))) break; if(k>1042021) break; }
    close(s); return 0;
}
