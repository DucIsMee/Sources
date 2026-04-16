// ============================================================
// ĐỀ 15 - Linux/Termux
// Timer1 (~7ms period): Nhập ký tự, lưu c, hiển thị hex
//                       Dừng khi c == '!'
// Timer2 (~3ms period): Hiển thị thời gian hệ thống
//                       Dừng khi c == '!'
//
// Termux không có Windows Timer Queue → dùng 2 pthread
// mỗi pthread tự sleep đúng chu kỳ (7ms / 3ms)
//
// Biên dịch: g++ De15.cpp -o De15 -lpthread
// ============================================================
#include <iostream>
#include <iomanip>
#include <pthread.h>
#include <unistd.h>     // usleep
#include <time.h>       // clock_gettime
using namespace std;

// ── Biến toàn cục ───────────────────────────────────────────
volatile char c = '\0';
volatile bool timer1Done = false;
volatile bool timer2Done = false;

// ── Timer1: Nhập ký tự, hiển thị hex, period ~7ms ───────────
// Câu 1 + 2
void* threadTimer1(void*) {
    cout << "[Timer1] Nhap ky tu (nhap '!' de thoat):\n";
    while (true) {
        char ch;
        cin >> ch;
        c = ch;

        cout << "[Timer1] Ky tu: '" << c << "'"
             << "  Hex: 0x" << hex << uppercase
             << setw(2) << setfill('0') << (int)(unsigned char)c
             << dec << "\n";

        if (c == '!') {
            timer1Done = true;
            break;
        }
        usleep(7000); // ~7ms
    }
    cout << "[Timer1] Ket thuc.\n";
    return nullptr;
}

// ── Timer2: Hiển thị giờ hệ thống, period ~3ms ─────────────
// Câu 3 + 4
void* threadTimer2(void*) {
    while (c != '!') {
        // Lấy thời gian hệ thống
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);

        struct tm* t = localtime(&ts.tv_sec);
        long ms = ts.tv_nsec / 1000000;

        cout << "[Timer2] "
             << setfill('0')
             << setw(2) << t->tm_hour << ":"
             << setw(2) << t->tm_min  << ":"
             << setw(2) << t->tm_sec  << "."
             << setw(3) << ms         << "\n";

        usleep(3000); // ~3ms
    }
    timer2Done = true;
    cout << "[Timer2] Ket thuc.\n";
    return nullptr;
}

int main() {
    pthread_t t1, t2;

    // Câu 4: Kích hoạt Timer2 trước, rồi Timer1
    pthread_create(&t2, nullptr, threadTimer2, nullptr);
    pthread_create(&t1, nullptr, threadTimer1, nullptr);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    cout << "[Main] Chuong trinh ket thuc.\n";
    return 0;
}
