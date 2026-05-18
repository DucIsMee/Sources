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

    mt19937 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());
    while (true) {
        int k = (int)rng();
        int32_t x = htonl(k);
        if (!send_all(sock, (char*)&x, sizeof(x))) break;
        if (k > 1042021) break;
    }

    close(sock);
    return 0;
}
