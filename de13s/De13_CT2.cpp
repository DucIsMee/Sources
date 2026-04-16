// ============================================================
// ĐỀ 13 - CT2 (READER) - Linux/Termux
// Đọc ký tự từ vidu.txt, hiển thị mã hex
// Dừng khi đọc '#', in số lượng ký tự 'A'
// Biên dịch: g++ De13_CT2.cpp -o CT2 -lpthread
// ============================================================
#include <iostream>
#include <fstream>
#include <iomanip>
#include <pthread.h>
#include <unistd.h>
using namespace std;

// Câu 3 + 4: Vòng lặp đọc file
void* funcReader(void*) {
    int countA = 0;
    long pos = 0; // vị trí đọc tiếp theo

    cout << "[CT2] Dang cho du lieu tu vidu.txt...\n";

    while (true) {
        ifstream fin("vidu.txt", ios::binary);
        if (!fin.is_open()) { usleep(100000); continue; }

        fin.seekg(pos);
        char c;
        if (!fin.get(c)) {
            fin.close();
            usleep(50000); // chưa có ký tự mới
            continue;
        }
        pos = fin.tellg();
        fin.close();

        cout << "[CT2] Doc duoc: '" << c << "'"
             << "  Hex: 0x" << hex << uppercase
             << setw(2) << setfill('0') << (int)(unsigned char)c
             << dec << "\n";

        if (c == 'A') countA++;

        if (c == '#') {
            cout << "[CT2] Gap '#', thoat.\n";
            cout << "[CT2] So luong ky tu 'A': " << countA << "\n";
            break;
        }
    }
    return nullptr;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, nullptr, funcReader, nullptr);
    pthread_join(tid, nullptr);
    return 0;
}
