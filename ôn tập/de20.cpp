#include <bits/stdc++.h>
using namespace std;
vector<char> Q;
mutex mtx;
atomic<bool> stop(false);
void task1(){
    while(true){
        char c;
        cout<<"Nhap ky tu: ";
        cin>>c;
        if(c=='#'){
            cout<<"Ket thuc!"<<endl;
            stop=true;
            break;
        }
        {
            lock_guard<mutex> lock(mtx);
            Q.push_back(c);
        }
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}
void task2(){
    while(!stop){
        vector<char> snapshot;
        {
            lock_guard<mutex> lock(mtx);
            snapshot = Q;
        }
        cout<<"Ky tu vua nhap: ";
        for(char c : snapshot){
            cout<<" "<<c;
        }
        cout<<endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}
int main(){
    thread t1(task1);
    thread t2(task2);
    t1.join();
    t2.join();
    return 0;
}