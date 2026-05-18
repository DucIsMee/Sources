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
  while(true){
    int n; if(!(cin>>n)) break;
    int32_t nn=htonl(n); if(!send_all(s,(char*)&nn,sizeof(nn))) break;
    if(n<=0) break;
    vector<int32_t>a(n); for(int i=0;i<n;i++) cin>>a[i];
    for(int i=n-1;i>=0;--i){ int32_t v=htonl(a[i]); if(!send_all(s,(char*)&v,sizeof(v))) goto END; }
  }
END: close(s); return 0;
}
