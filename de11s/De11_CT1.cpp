// ============================================================
// ĐỀ 11 - CT1 (CLIENT) - Linux/Termux
// Nhập mảng số thực, truyền n và mảng đến CT2 (server)
// Biên dịch: g++ De11_CT1.cpp -o CT1 -lpthread
// Chạy: ./CT2 trước, rồi ./CT1
// ============================================================
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define SERVER_IP "127.0.0.1"
#define PORT 5000

int connectToServer() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &addr.sin_addr);

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("[CT1] Khong the ket noi");
        exit(1);
    }
    cout << "[CT1] Da ket noi den server.\n";
    return sock;
}

void nhapVaTruyen(int sock) {
    while (true) {
        int n;
        cout << "\nNhap so phan tu (n<=0 de thoat): ";
        cin >> n;

        send(sock, &n, sizeof(int), 0);
        if (n <= 0) { cout << "[CT1] Thoat.\n"; break; }

        float* arr = new float[n];
        for (int i = 0; i < n; i++) {
            cout << "  arr[" << i << "]: ";
            cin >> arr[i];
        }
        send(sock, arr, n * sizeof(float), 0);
        cout << "[CT1] Da gui " << n << " phan tu.\n";
        delete[] arr;
    }
}

int main() {
    int sock = connectToServer();
    nhapVaTruyen(sock);
    close(sock);
    return 0;
}
