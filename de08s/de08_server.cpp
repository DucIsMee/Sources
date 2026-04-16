#include <iostream>
#include <thread>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define PORT 5000
#define IP   "127.0.0.1"

double minReceived = 1e18;

void receiveLoop() {
    int srv = socket(AF_INET, SOCK_STREAM, 0);
    if (srv < 0) { cout << "[CT2] Loi tao socket!" << endl; return; }

    int opt = 1;
    setsockopt(srv, SOL_SOCKET, SO_REUSEADDR, (void*)&opt, sizeof(opt));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(IP);

    if (bind(srv, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        cout << "[CT2] Loi bind!" << endl;
        close(srv); return;
    }

    listen(srv, 1);
    cout << "[CT2] Dang lang nghe " << IP << ":" << PORT << endl;

    int client = accept(srv, nullptr, nullptr);
    if (client < 0) { close(srv); return; }
    cout << "[CT2] CT1 da ket noi!" << endl;

    while (true) {
        double t;
        int bytes = recv(client, (char*)&t, sizeof(t), 0);
        if (bytes <= 0) { cout << "[CT2] CT1 ngat ket noi." << endl; break; }

        if (t < minReceived) minReceived = t;
        cout << "[CT2] Nhan t = " << t << " | Min = " << minReceived << endl;

        if (t >= 0.8 && t <= 0.82) {
            cout << "[CT2] t nam trong [0.8, 0.82] -> Thoat!" << endl;
            break;
        }
    }

    close(client);
    close(srv);
}

int main() {
    cout << "=== DE 08: CT2 (Server) ===" << endl;
    thread t(receiveLoop);
    t.join();
    cout << "[CT2] Ket thuc. Min = " << minReceived << endl;
    return 0;
}
