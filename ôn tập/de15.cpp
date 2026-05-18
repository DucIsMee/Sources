// De15: Timer1 (read char, show hex) every 7ms; Timer2 (show time) every 3ms
#include <bits/stdc++.h>
#include <atomic>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>

using namespace std::chrono_literals;

std::atomic<char> g_c{0};
std::atomic<bool> g_stop{false};

struct TermRestore {
    struct termios oldt;
    bool valid=false;
    TermRestore(){
        if(tcgetattr(STDIN_FILENO,&oldt)==0) valid=true;
    }
    ~TermRestore(){ if(valid) tcsetattr(STDIN_FILENO,TCSANOW,&oldt); }
};

bool kbhit_char(char &out){
    fd_set set;
    struct timeval tv{0,0};
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO,&set);
    int rv = select(STDIN_FILENO+1,&set,nullptr,nullptr,&tv);
    if(rv>0 && FD_ISSET(STDIN_FILENO,&set)){
        char ch; ssize_t r = read(STDIN_FILENO,&ch,1);
        if(r==1){ out=ch; return true; }
    }
    return false;
}

void timer1_func(){ // every 7ms check for keyboard input
    // set terminal to non-canonical, no-echo
    struct termios newt;
    TermRestore tr;
    if(tr.valid){
        newt = tr.oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        newt.c_cc[VMIN] = 0;
        newt.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO,TCSANOW,&newt);
    }

    auto period = std::chrono::milliseconds(7);
    auto next = std::chrono::steady_clock::now();
    while(!g_stop){
        next += period;
        char ch;
        if(kbhit_char(ch)){
            g_c = ch;
            printf("Read char: %c  Hex: 0x%02X\n", (ch>=' ' && ch<127)?ch:'.', (unsigned char)ch);
            fflush(stdout);
            if(ch=='!') { g_stop = true; break; }
        }
        std::this_thread::sleep_until(next);
    }
}

void timer2_func(){ // every 3ms show system time until g_stop true
    auto period = std::chrono::milliseconds(3);
    auto next = std::chrono::steady_clock::now();
    while(!g_stop){
        next += period;
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        char buf[64];
        struct tm tmv;
        localtime_r(&t,&tmv);
        strftime(buf,sizeof(buf),"%H:%M:%S",&tmv);
        printf("Time: %s  current char: %c\n", buf, g_c.load());
        fflush(stdout);
        std::this_thread::sleep_until(next);
    }
}

int main(){
    printf("De15: two timers running. Type characters; '!' to quit.\n");
    std::thread t1(timer1_func);
    std::thread t2(timer2_func);
    t1.join();
    // ensure stop and join t2
    g_stop = true;
    if(t2.joinable()) t2.join();
    printf("Exiting.\n");
    return 0;
}
