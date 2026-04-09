// DE 08 - CT2: SERVER
// Chay truoc CT1
// Bien dich: g++ de08_server.cpp -o de08_server -std=c++17 -lpthread
// Chay: ./de08_server

#include <iostream>
#include <thread>
#include <atomic>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define PORT 5000
#define IP   "127.0.0.1"

atomic<bool> serverDone(false);
double minReceived = 1e18;

void receiveLoop() {
    // Tao socket
    int srv = socket(AF_INET, SOCK_STREAM, 0);
    if (srv < 0) {
        cout << "[CT2] Loi tao socket!" << endl;
        return;
    }

    // Cho phep reuse port
    int opt = 1;
    setsockopt(srv, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Bind
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, IP, &addr.sin_addr);

    if (bind(srv, (sockaddr*)&addr, sizeof(addr)) < 0) {
        cout << "[CT2] Loi bind port " << PORT << "!" << endl;
        close(srv);
        return;
    }

    listen(srv, 1);
    cout << "[CT2-Server] Dang lang nghe tai " << IP << ":" << PORT << endl;
    cout << "[CT2-Server] Cho CT1 ket noi..." << endl;

    // Chap nhan ket noi tu CT1
    int client = accept(srv, nullptr, nullptr);
    if (client < 0) {
        cout << "[CT2] Loi accept!" << endl;
        close(srv);
        return;
    }
    cout << "[CT2-Server] CT1 da ket noi!" << endl;

    // Nhan du lieu
    while (true) {
        double t;
        int bytes = recv(client, (char*)&t, sizeof(t), 0);
        if (bytes <= 0) {
            cout << "[CT2] CT1 ngat ket noi." << endl;
            break;
        }

        // Cap nhat min
        if (t < minReceived) minReceived = t;

        cout << "[CT2] Nhan t = " << t
             << " | Min hien tai = " << minReceived << endl;

        // Kiem tra khoang [0.8, 0.82]
        if (t >= 0.8 && t <= 0.82) {
            cout << "[CT2] t = " << t
                 << " nam trong [0.8, 0.82] -> Thoat!" << endl;
            break;
        }
    }

    close(client);
    close(srv);
    serverDone = true;
}

int main() {
    cout << "=== DE 08: CT2 (Server) ===" << endl;

    thread t(receiveLoop);
    t.join();

    cout << "[CT2] Ket thuc. Gia tri nho nhat da nhan: " << minReceived << endl;
    return 0;
}
