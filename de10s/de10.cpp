// DE 10 - C++ Multithreading (Async)
// Task1: Nhap lien tuc ky tu, luu vao mang A, dung khi gap '#'
// Task2: Hien thi cac ky tu trong A va bo nho RAM con lai
//        Dung khi Task1 dung

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>

#ifdef _WIN32
  #include <windows.h>
#else
  #include <sys/sysinfo.h>
#endif

using namespace std;

vector<char> A;        // Mang luu ky tu
mutex mtxA;            // Bao ve truy cap A
atomic<bool> task1Done(false);

// Lay RAM con lai (MB)
long long getFreeRAM_MB() {
#ifdef _WIN32
    MEMORYSTATUSEX ms;
    ms.dwLength = sizeof(ms);
    GlobalMemoryStatusEx(&ms);
    return (long long)(ms.ullAvailPhys / (1024 * 1024));
#else
    struct sysinfo info;
    sysinfo(&info);
    return (long long)(info.freeram / (1024 * 1024));
#endif
}

// Task1: Nhap ky tu, luu vao mang A, dung khi '#'
void task1Func() {
    cout << "[Task1] Bat dau nhap ky tu. Nhap '#' de dung." << endl;
    char c;
    while (true) {
        cout << "[Task1] Nhap ky tu: ";
        cin >> c;
        if (c == '#') {
            cout << "[Task1] Nhan '#', dung nhap." << endl;
            break;
        }
        lock_guard<mutex> lk(mtxA);
        A.push_back(c);
        cout << "[Task1] Da them '" << c << "' vao mang." << endl;
    }
    task1Done = true;
}

// Task2: Hien thi mang A va RAM con lai, dung khi Task1 dung
void task2Func() {
    cout << "[Task2] Bat dau hien thi..." << endl;
    while (!task1Done.load()) {
        {
            lock_guard<mutex> lk(mtxA);
            cout << "[Task2] Mang A: [";
            for (size_t i = 0; i < A.size(); i++) {
                if (i > 0) cout << ", ";
                cout << "'" << A[i] << "'";
            }
            cout << "]" << endl;
        }

        long long ram = getFreeRAM_MB();
        cout << "[Task2] Bo nho RAM con lai: " << ram << " MB" << endl;
        cout << "---" << endl;

        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    // Hien thi lan cuoi
    lock_guard<mutex> lk(mtxA);
    cout << "[Task2] Mang cuoi cung: [";
    for (size_t i = 0; i < A.size(); i++) {
        if (i > 0) cout << ", ";
        cout << "'" << A[i] << "'";
    }
    cout << "]" << endl;
    cout << "[Task2] RAM con lai: " << getFreeRAM_MB() << " MB" << endl;
    cout << "[Task2] Ket thuc." << endl;
}

int main() {
    cout << "=== DE 10: Task1 + Task2 (Async) ===" << endl;

    thread t1(task1Func);
    thread t2(task2Func);

    t1.join();
    t2.join();

    cout << "[main] Hoan thanh." << endl;
    return 0;
}
