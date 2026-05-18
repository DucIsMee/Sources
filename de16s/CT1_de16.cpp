#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

bool send_all(int s, const char* buf, int len) {
  for (int sent = 0; sent < len; ) {
    int n = send(s, buf + sent, len - sent, 0);
    if (n <= 0) return false;
    sent += n;
  }
  return true;
}

int main() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  sockaddr_in srv{};
  srv.sin_family = AF_INET;
  srv.sin_port = htons(5000);
  inet_pton(AF_INET, "127.0.0.1", &srv.sin_addr);

  if (connect(sock, (sockaddr*)&srv, sizeof(srv)) < 0) return 1;

  while (true) {
    int n;
    if (!(cin >> n)) break;

    int32_t nn = htonl(n);
    if (!send_all(sock, (char*)&nn, sizeof(nn))) break;
    if (n <= 0) break;

    vector<int32_t> a(n);
    for (int& x : a) cin >> x;

    for (int i = n - 1; i >= 0; --i) {
      int32_t v = htonl(a[i]);
      if (!send_all(sock, (char*)&v, sizeof(v))) goto done;
    }
  }

done:
  close(sock);
  return 0;
}
