// ============================================================
// ĐỀ 14 - Linux/Termux
// Task1 (pthread): Nhập chuỗi → ghi từng dòng vào vidu.txt
//                 Dừng khi nhập "quit"
// Task2 (pthread): Đọc vidu.txt liên tục, hiển thị + đếm dòng
//                 Dừng khi đọc "quit"
// Biên dịch: g++ De14.cpp -o De14 -lpthread
// ============================================================
#include <iostream>
#include <fstream>
#include <string>
#include <pthread.h>
#include <unistd.h>
using namespace std;

// ── Biến toàn cục ───────────────────────────────────────────
string st = "";
volatile bool task1Done = false;

// ── Task1 ────────────────────────────────────────────────────
void* threadTask1(void*) {
    remove("vidu.txt");
    cout << "[Task1] Nhap chuoi (nhap 'quit' de thoat):\n";

    while (true) {
        cout << "> ";
        getline(cin, st);

        ofstream fout("vidu.txt", ios::app);
        if (fout.is_open()) {
            fout << st << "\n";
            fout.flush();
            fout.close();
        }

        if (st == "quit") {
            task1Done = true;
            cout << "[Task1] Ket thuc.\n";
            break;
        }
    }
    return nullptr;
}

// ── Task2 ────────────────────────────────────────────────────
void* threadTask2(void*) {
    long pos = 0;
    int lineCount = 0;

    cout << "[Task2] Dang cho du lieu...\n";

    while (true) {
        ifstream fin("vidu.txt");
        if (!fin.is_open()) { usleep(100000); continue; }

        fin.seekg(pos);
        string line;
        if (!getline(fin, line)) {
            fin.close();
            if (task1Done) break;
            usleep(100000);
            continue;
        }
        pos = fin.tellg();
        lineCount++;
        fin.close();

        cout << "[Task2] Doc: \"" << line << "\"\n";
        cout << "[Task2] Tong so dong: " << lineCount << "\n";

        if (line == "quit") {
            cout << "[Task2] Gap 'quit', thoat.\n";
            break;
        }
    }
    cout << "[Task2] Ket thuc. Tong dong: " << lineCount << "\n";
    return nullptr;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, nullptr, threadTask1, nullptr);
    pthread_create(&t2, nullptr, threadTask2, nullptr);
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    return 0;
}
