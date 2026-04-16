// DE 08 - CT1: CLIENT
// Chay sau CT2
// Bien dich: g++ de08_client.cpp -o de08_client -std=c++17 -lpthread
// Chay: ./de08_client

#include <iostream>
#include <thread>
#include <atomic>
#include <cstdlib>
#include <ctime>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define PORT 5000
#define IP   "127.0.0.1"

atomic<bool> clientDone(false);
double t_global = 0.0;

double randomFloat() {
    // Sinh so thuc ngau nhien trong [0.0, 1.0]
    return (double)rand() / RAND_MAX;
}

void generateLoop(int sock) {
    srand((unsigned)time(nullptr));

    while (true) {
        t_global = randomFloat();
        cout << "[CT1] Sinh t = " << t_global << endl;

        // Truyen t sang CT2 qua socket
        int bytes = send(sock, (char*)&t_global, sizeof(t_global), 0);
        if (bytes < 0) {
            cout << "[CT1] Loi gui du lieu!" << endl;
            break;
        }

        // Kiem tra dieu kien dung
        if (t_global >= 0.8 && t_global <= 0.82) {
            cout << "[CT1] t = " << t_global
                 << " roi vao [0.8, 0.82] -> CT1 dung." << endl;
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(300));
    }

    clientDone = true;
}

int main() {
    cout << "=== DE 08: CT1 (Client) ===" << endl;

    // Tao socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cout << "[CT1] Loi tao socket!" << endl;
        return 1;
    }

    // Ket noi den CT2
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, IP, &addr.sin_addr);

    cout << "[CT1] Dang ket noi den CT2 tai " << IP << ":" << PORT << "..." << endl;
    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) != 0) {
        cout << "[CT1] Khong the ket noi den CT2! Hay chay CT2 truoc." << endl;
        close(sock);
        return 1;
    }
    cout << "[CT1] Da ket noi thanh cong!" << endl;

    // Dat ham vao luong
    thread t(generateLoop, sock);
    t.join();

    close(sock);
    cout << "[CT1] Ket thuc." << endl;
    return 0;
}
