#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
bool recv_all(int s,char*buf,int len){int t=0;while(t<len){ssize_t r=recv(s,buf+t,len-t,0); if(r<=0) return false; t+=r;} return true;}
int main(){
  int ls=socket(AF_INET,SOCK_STREAM,0);
  int opt=1; setsockopt(ls,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
  sockaddr_in a{AF_INET,htons(5000),{INADDR_ANY}}; bind(ls,(sockaddr*)&a,sizeof(a)); listen(ls,1);
  int c=accept(ls,nullptr,nullptr);
  while(true){ int32_t nn; if(!recv_all(c,(char*)&nn,sizeof(nn))){ break;} int n=ntohl(nn); if(n<=0) break; vector<int32_t>v(n); for(int i=0;i<n;i++){int32_t x; if(!recv_all(c,(char*)&x,sizeof(x))){ goto END;} v[i]=ntohl(x);} for(int x:v) cout<<x<<" "; cout<<"\n"; }
END: close(c); close(ls); return 0;
}
