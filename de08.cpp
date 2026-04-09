// =============================================
// DE 08 - CT1: CLIENT (chay sau CT2)
// Tao so thuc ngau nhien t, truyen qua Socket den CT2
// Dung khi t roi vao [0.8, 0.82]
// =============================================
// DE 08 - CT2: SERVER (chay truoc CT1)
// Nhan gia tri t tu CT1, kiem tra khoang [0.8, 0.82]
// =============================================

// =========================
// FILE: de08_server.cpp (CT2)
// Bien dich: g++ de08_server.cpp -o server -lws2_32  (Windows)
// Chay server truoc: ./server
// =========================

/*
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

#define PORT 5000
#define IP   "127.0.0.1"

double minReceived = 1e18;

void receiveLoop() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET srv = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, IP, &addr.sin_addr);

    bind(srv, (sockaddr*)&addr, sizeof(addr));
    listen(srv, 1);
    cout << "[CT2-Server] Dang lang nghe tai " << IP << ":" << PORT << endl;

    SOCKET client = accept(srv, nullptr, nullptr);
    cout << "[CT2-Server] CT1 da ket noi!" << endl;

    while (true) {
        double t;
        int bytes = recv(client, (char*)&t, sizeof(t), 0);
        if (bytes <= 0) break;

        if (t < minReceived) minReceived = t;
        cout << "[CT2-Server] Nhan t = " << t
             << " | Min hien tai = " << minReceived << endl;

        if (t >= 0.8 && t <= 0.82) {
            cout << "[CT2-Server] t = " << t << " roi vao [0.8, 0.82] -> Thoat!" << endl;
            break;
        }
    }

    closesocket(client);
    closesocket(srv);
    WSACleanup();
}

int main() {
    thread t(receiveLoop);
    t.join();
    return 0;
}
*/

// =========================
// FILE: de08_client.cpp (CT1)
// Bien dich: g++ de08_client.cpp -o client -lws2_32
// Chay: ./client
// =========================

/*
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <cstdlib>
#include <ctime>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

#define PORT 5000
#define IP   "127.0.0.1"

double t_global = 0.0;

double randomFloat() {
    return (double)rand() / RAND_MAX; // [0.0, 1.0]
}

void generateLoop(SOCKET sock) {
    srand((unsigned)time(nullptr));
    while (true) {
        t_global = randomFloat();
        cout << "[CT1-Client] Sinh t = " << t_global << endl;

        // Truyen t sang CT2
        send(sock, (char*)&t_global, sizeof(t_global), 0);

        if (t_global >= 0.8 && t_global <= 0.82) {
            cout << "[CT1-Client] t roi vao [0.8, 0.82] -> Dung." << endl;
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, IP, &addr.sin_addr);

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) != 0) {
        cout << "[CT1] Khong the ket noi den CT2!" << endl;
        return 1;
    }
    cout << "[CT1] Da ket noi den CT2." << endl;

    thread t(generateLoop, sock);
    t.join();

    closesocket(sock);
    WSACleanup();
    return 0;
}
*/

// =====================================================
// PHIEN BAN DOC LAP (1 file, khong can socket that):
// Simulate CT1 + CT2 trong 1 chuong trinh de test nhanh
// =====================================================
#include <iostream>
#include <thread>
#include <atomic>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;

queue<double> dataQueue;
mutex mtx;
condition_variable cv;
atomic<bool> done(false);

double minReceived = 1e18;

// CT1 - Sinh so ngau nhien va day vao queue
void ct1_client() {
    srand((unsigned)time(nullptr));
    while (true) {
        double t = (double)rand() / RAND_MAX;
        cout << "[CT1] Sinh t = " << t << endl;

        {
            lock_guard<mutex> lk(mtx);
            dataQueue.push(t);
        }
        cv.notify_one();

        if (t >= 0.8 && t <= 0.82) {
            cout << "[CT1] t = " << t << " roi vao [0.8, 0.82] -> CT1 dung." << endl;
            done = true;
            cv.notify_one();
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

// CT2 - Nhan va kiem tra
void ct2_server() {
    while (true) {
        unique_lock<mutex> lk(mtx);
        cv.wait(lk, [] { return !dataQueue.empty() || done.load(); });

        while (!dataQueue.empty()) {
            double t = dataQueue.front();
            dataQueue.pop();
            lk.unlock();

            if (t < minReceived) minReceived = t;
            cout << "[CT2] Nhan t = " << t
                 << " | Min = " << minReceived << endl;

            if (t >= 0.8 && t <= 0.82) {
                cout << "[CT2] Thoat! t = " << t << " nam trong [0.8, 0.82]" << endl;
                return;
            }

            lk.lock();
        }

        if (done.load() && dataQueue.empty()) break;
    }
    cout << "[CT2] Ket thuc." << endl;
}

int main() {
    cout << "=== DE 08: CT1 (Client) + CT2 (Server) ===" << endl;

    // Chay CT2 truoc, CT1 sau (theo dau bai)
    thread server(ct2_server);
    thread client(ct1_client);

    client.join();
    server.join();

    cout << "[main] Hoan thanh." << endl;
    return 0;
}
