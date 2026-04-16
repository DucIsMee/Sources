// ============================================================
// ĐỀ 11 - CT2 (SERVER) - Linux/Termux
// Nhận n và mảng số thực từ CT1, tính trung bình cộng
// Câu 4: hàm nhận đặt vào pthread
// Biên dịch: g++ De11_CT2.cpp -o CT2 -lpthread
// Chạy CT2 trước, rồi chạy CT1
// ============================================================
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;

#define PORT 5000

int clientSock = -1;

void* nhanVaXuLy(void*) {
    while (true) {
        int n;
        int ret = recv(clientSock, &n, sizeof(int), MSG_WAITALL);
        if (ret <= 0) break;

        cout << "\n[CT2] Nhan n = " << n << "\n";
        if (n <= 0) { cout << "[CT2] Thoat.\n"; break; }

        float* arr = new float[n];
        recv(clientSock, arr, n * sizeof(float), MSG_WAITALL);

        double sum = 0;
        cout << "[CT2] Mang: ";
        for (int i = 0; i < n; i++) { cout << arr[i] << " "; sum += arr[i]; }
        cout << "\n[CT2] Trung binh cong: " << sum / n << "\n";

        delete[] arr;
    }
    return nullptr;
}

int main() {
    int serverSock = socket(AF_INET, SOCK_STREAM, 0);

    // Cho phép reuse port ngay sau khi tắt
    int opt = 1;
    setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSock, (sockaddr*)&addr, sizeof(addr));
    listen(serverSock, 1);

    cout << "[CT2] Lang nghe port " << PORT << "...\n";
    sockaddr_in clientAddr{};
    socklen_t len = sizeof(clientAddr);
    clientSock = accept(serverSock, (sockaddr*)&clientAddr, &len);
    cout << "[CT2] Client da ket noi.\n";
    close(serverSock);

    // Câu 4: Đặt hàm vào pthread
    pthread_t tid;
    pthread_create(&tid, nullptr, nhanVaXuLy, nullptr);
    pthread_join(tid, nullptr);

    close(clientSock);
    cout << "[CT2] Ket thuc.\n";
    return 0;
}
