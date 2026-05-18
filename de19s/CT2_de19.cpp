#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
bool recv_all(int s,char*buf,int len){int t=0;while(t<len){ssize_t r=recv(s,buf+t,len-t,0); if(r<=0) return false; t+=r;} return true;}
int main(){
    int ls=socket(AF_INET,SOCK_STREAM,0); int opt=1; setsockopt(ls,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    sockaddr_in a{AF_INET,htons(5000),{INADDR_ANY}}; bind(ls,(sockaddr*)&a,sizeof(a)); listen(ls,1);
    int c=accept(ls,nullptr,nullptr);
    int cur=INT_MIN; while(true){ int32_t kk; if(!recv_all(c,(char*)&kk,sizeof(kk))) break; int k=ntohl(kk); if(k>1042021) break; cur=max(cur,k); printf("0x%X\n",cur);} close(c); close(ls); return 0;
}
