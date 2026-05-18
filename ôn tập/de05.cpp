#include <iostream>
#include <winsock2.h>
#include <thread>
#include <ctime>

#pragma comment(lib,"ws2_32.lib")
using namespace std;

void client() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(s, (sockaddr*)&server, sizeof(server));

    srand((unsigned int)time(0));

    while (true) {
        int k = rand();

        send(s, (char*)&k, sizeof(k), 0);

        cout << "Gui: " << k << endl;

        if (k > 10000 && k % 2022 == 0)
            break;

        Sleep(100);
    }

    closesocket(s);
    WSACleanup();
}

int main() {
    client();
    return 0;
}