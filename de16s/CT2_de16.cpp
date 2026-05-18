#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

bool recv_all(int s, char* buf, int len) {
  for (int recvd = 0; recvd < len; ) {
    int n = recv(s, buf + recvd, len - recvd, 0);
    if (n <= 0) return false;
    recvd += n;
  }
  return true;
}

int main() {
  int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
  int opt = 1;
  setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(5000);
  addr.sin_addr.s_addr = INADDR_ANY;

  bind(listen_sock, (sockaddr*)&addr, sizeof(addr));
  listen(listen_sock, 1);

  int client = accept(listen_sock, nullptr, nullptr);
  while (true) {
    int32_t nn;
    if (!recv_all(client, (char*)&nn, sizeof(nn))) break;

    int n = ntohl(nn);
    if (n <= 0) break;

    vector<int32_t> a(n);
    for (int i = 0; i < n; ++i) {
      if (!recv_all(client, (char*)&a[i], sizeof(a[i]))) goto done;
      a[i] = ntohl(a[i]);
    }

    for (int x : a) cout << x << ' ';
    cout << '\n';
  }

done:
  close(client);
  close(listen_sock);
  return 0;
}
