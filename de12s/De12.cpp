// ============================================================
// ĐỀ 12 - Linux/Termux
// Task1 (pthread): Nhập ký tự → bộ đệm vòng, dừng khi '!'
// Task2 (pthread): Hiển thị bộ đệm liên tục
// Task3 (đồng bộ): Đếm ký tự 'A' sau khi Task1 xong
// Biên dịch: g++ De12.cpp -o De12 -lpthread
// ============================================================
#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;

// ── Bộ đệm vòng ─────────────────────────────────────────────
#define BUF_SIZE 256
struct CircularBuffer {
    char data[BUF_SIZE];
    int  head = 0, tail = 0, count = 0;

    bool isFull()  { return count == BUF_SIZE; }
    bool isEmpty() { return count == 0; }

    void push(char c) {
        if (isFull()) return;
        data[tail] = c;
        tail = (tail + 1) % BUF_SIZE;
        count++;
    }

    void display() {
        if (isEmpty()) { cout << "[Buffer] (trong)\n"; return; }
        cout << "[Buffer] ";
        int idx = head;
        for (int i = 0; i < count; i++) {
            cout << data[idx];
            idx = (idx + 1) % BUF_SIZE;
        }
        cout << "\n";
    }

    int countChar(char target) {
        int cnt = 0, idx = head;
        for (int i = 0; i < count; i++) {
            if (data[idx] == target) cnt++;
            idx = (idx + 1) % BUF_SIZE;
        }
        return cnt;
    }
};

// ── Biến toàn cục ───────────────────────────────────────────
CircularBuffer C;
volatile bool task1Done = false;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

// ── Task1 ────────────────────────────────────────────────────
void* threadTask1(void*) {
    cout << "[Task1] Nhap ky tu (nhap '!' de thoat):\n";
    while (true) {
        char c;
        cin >> c;
        pthread_mutex_lock(&mtx);
        C.push(c);
        pthread_mutex_unlock(&mtx);
        if (c == '!') { task1Done = true; break; }
    }
    cout << "[Task1] Ket thuc.\n";
    return nullptr;
}

// ── Task2 ────────────────────────────────────────────────────
void* threadTask2(void*) {
    while (!task1Done) {
        pthread_mutex_lock(&mtx);
        C.display();
        pthread_mutex_unlock(&mtx);
        usleep(500000); // 500ms
    }
    // Hiển thị lần cuối
    pthread_mutex_lock(&mtx);
    C.display();
    pthread_mutex_unlock(&mtx);
    cout << "[Task2] Ket thuc.\n";
    return nullptr;
}

// ── Task3 (đồng bộ) ─────────────────────────────────────────
void funcTask3() {
    int cnt = C.countChar('A');
    cout << "[Task3] So ky tu 'A' trong bo dem: " << cnt << "\n";
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t2, nullptr, threadTask2, nullptr); // Task2 trước
    pthread_create(&t1, nullptr, threadTask1, nullptr);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    funcTask3(); // Task3 đồng bộ sau Task1
    return 0;
}
