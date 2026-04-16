// DE 09 - C++ Multithreading (Async)
// Task1: Nhap so nguyen tu ban phim, luu vao linked list S
//        Dung khi nhap -1
// Task2: Lien tuc hien thi cac so trong danh sach S
//        Dung khi Task1 ket thuc

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <list>
using namespace std;

list<int> S;           // Danh sach lien ket
mutex mtxList;         // Bao ve truy cap S
atomic<bool> task1Done(false);  // Co biet Task1 da xong

// Task1: Nhap lien tuc so nguyen, luu vao S, dung khi nhap -1
void task1Func() {
    cout << "[Task1] Bat dau nhap. Nhap -1 de dung." << endl;
    int n;
    while (true) {
        cout << "[Task1] Nhap so: ";
        cin >> n;
        if (n == -1) {
            cout << "[Task1] Da nhap -1, ket thuc." << endl;
            break;
        }
        lock_guard<mutex> lk(mtxList);
        S.push_back(n);
        cout << "[Task1] Da them " << n << " vao danh sach." << endl;
    }
    task1Done = true;
}

// Task2: Lien tuc hien thi danh sach S, dung khi Task1 ket thuc
void task2Func() {
    cout << "[Task2] Bat dau hien thi danh sach..." << endl;
    while (!task1Done.load()) {
        {
            lock_guard<mutex> lk(mtxList);
            cout << "[Task2] Danh sach S: [";
            bool first = true;
            for (int x : S) {
                if (!first) cout << ", ";
                cout << x;
                first = false;
            }
            cout << "]" << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(800));
    }

    // Hien thi lan cuoi sau khi Task1 ket thuc
    lock_guard<mutex> lk(mtxList);
    cout << "[Task2] Danh sach cuoi cung: [";
    bool first = true;
    for (int x : S) {
        if (!first) cout << ", ";
        cout << x;
        first = false;
    }
    cout << "]" << endl;
    cout << "[Task2] Ket thuc." << endl;
}

int main() {
    cout << "=== DE 09: Task1 + Task2 (Async) ===" << endl;

    // Task1 va Task2 chay khong dong bo
    thread t1(task1Func);
    thread t2(task2Func);

    t1.join();
    t2.join();

    cout << "[main] Ca hai task da hoan thanh." << endl;
    return 0;
}
