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
    int current_max = INT_MIN;

    while (true) {
        int32_t x;
        if (!recv_all(client, (char*)&x, sizeof(x))) break;

        int k = ntohl(x);
        if (k > 1042021) break;

        current_max = max(current_max, k);
        printf("0x%X\n", current_max);
    }

    close(client);
    close(listen_sock);
    return 0;
}
