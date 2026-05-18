#include <bits/stdc++.h>

using namespace std;
int minVal = INT_MAX;
mutex mtx;
bool stop=false;
void task1(){
    while(true){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(INT_MIN,INT_MAX);
        int i=dis(gen);
        {
            lock_guard<mutex> lock(mtx);
            if((minVal==INT_MAX || minVal>i) && i > 2021){
                minVal=i;
            }
        }
        if(minVal%22092021==0){cout<<"Ket thuc!";stop=true;break;}
        this_thread::sleep_for(chrono::milliseconds(1));
    }
}
void task2(){
    while(!stop){
        {
            lock_guard<mutex> lock(mtx);
            cout<<"Min: "<<minVal<<endl;
        }
        this_thread::sleep_for(chrono::seconds(2));
    }
}
int main(){
    thread t1(task1);
    thread t2(task2);
    t1.join();
    t2.join();
    return 0;
}