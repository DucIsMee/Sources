// DE 07 - C++ Multithreading
// Thread1: Mo file, doc tung ky tu, hien thi hex
// Thread2: Vong lap chay trong khi Thread1 con chay, hien thi ky tu da doc

#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>
#include <iomanip>
#include <string>
using namespace std;

atomic<bool> thread1Running(false);
atomic<char> lastCharRead('\0');

// Thread1: Mo file, doc tung ky tu, hien thi hex
void thread1Func() {
    thread1Running = true;

    // Tao file mau neu chua co
    {
        ofstream init("vd.txt", ios::app);
        // Khong ghi gi, chi dam bao file ton tai
    }

    ifstream file("vd.txt");
    if (!file.is_open()) {
        cout << "[Thread1] Khong mo duoc file vd.txt!" << endl;
        thread1Running = false;
        return;
    }

    cout << "[Thread1] Bat dau doc file vd.txt..." << endl;
    char c;
    while (file.get(c)) {
        lastCharRead = c;
        cout << "[Thread1] Ky tu: '" << c << "' | Hex: 0x"
             << hex << uppercase << setw(2) << setfill('0')
             << (int)(unsigned char)c << dec << endl;
        this_thread::sleep_for(chrono::milliseconds(200));
    }

    cout << "[Thread1] Da doc het file." << endl;
    file.close();
    thread1Running = false;
}

// Thread2: Vong lap chay trong khi Thread1 con chay
void thread2Func() {
    cout << "[Thread2] Bat dau chay..." << endl;
    while (thread1Running.load()) {
        char c = lastCharRead.load();
        if (c != '\0') {
            cout << "[Thread2] Ky tu hien thi tu Thread1: '" << c << "'" << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << "[Thread2] Thread1 da dung, Thread2 thoat." << endl;
}

int main() {
    // Tao file vd.txt mau
    ofstream f("vd.txt");
    f << "Hello, De 07!\nC++ Threads.";
    f.close();

    // Thiet lap Thread2 truoc, kich hoat Thread1 sau
    thread t2(thread2Func);
    thread t1(thread1Func);

    t1.join();
    t2.join();

    cout << "[main] Ca hai thread da hoan thanh." << endl;
    return 0;
}
