// ============================================================
// ĐỀ 13 - CT1 (WRITER) - Linux/Termux
// Nhập ký tự, ghi vào vidu.txt, dừng khi '#'
// Biên dịch: g++ De13_CT1.cpp -o CT1 -lpthread
// Chạy cả CT1 và CT2 đồng thời (2 terminal)
// ============================================================
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

// Câu 1 + 2: Hàm ghi ký tự vào file
void* funcWriter(void*) {
    cout << "[CT1] Nhap ky tu (nhap '#' de thoat):\n";
    while (true) {
        char c;
        cin >> c;

        // Ghi vào file (append)
        ofstream fout("vidu.txt", ios::app);
        if (fout.is_open()) {
            fout << c;
            fout.flush();
            fout.close();
        }

        if (c == '#') {
            cout << "[CT1] Da ghi '#', ket thuc.\n";
            break;
        }
    }
    return nullptr;
}

int main() {
    // Xóa file cũ
    remove("vidu.txt");

    pthread_t tid;
    pthread_create(&tid, nullptr, funcWriter, nullptr);
    pthread_join(tid, nullptr);
    return 0;
}
