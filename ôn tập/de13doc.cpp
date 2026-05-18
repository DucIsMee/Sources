#include <iostream>
#include <fstream>
#include <thread>
using namespace std;

void ghiFile() {
    ofstream fout("vidu.txt", ios::out);
    // ios::out để tạo mới file, tránh dữ liệu cũ

    char c;

    if (!fout) {
        cout << "Khong mo duoc file!\n";
        return;
    }

    cout << "Nhap ky tu (# de thoat):\n";

    while (true) {
        cin.get(c);   // đọc đúng 1 ký tự

        // Bỏ qua Enter nếu không muốn lưu
        if (c == '\n')
            continue;

        fout << c;
        fout.flush(); // ghi ngay xuống file

        if (c == '#')
            break;
    }

    fout.close();
    cout << "Da ghi xong!\n";
}

void docFile() {
    ifstream fin("vidu.txt", ios::in);

    if (!fin) {
        cout << "Khong mo duoc file!\n";
        return;
    }

    cout << "Noi dung file:\n";
    char c;
    while (fin.get(c)) {
        cout << c;
    }
    cout << "\n";

    fin.close();
    cout << "Da doc xong!\n";
}

int main() {
    int choice;

    cout << "1. Ghi file\n";
    cout << "2. Doc file\n";
    cout << "Chon (1 or 2): ";
    cin >> choice;
    cin.ignore();  // bỏ qua Enter sau khi nhập số

    if (choice == 1) {
        thread t(ghiFile);
        t.join();
    } else if (choice == 2) {
        thread t(docFile);
        t.join();
    } else {
        cout << "Lua chon khong hop le!\n";
    }

    return 0;
}
