#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <cstdio>
#include <fstream>
using namespace std;
string st;
bool done=false;
void task1(){
    ofstream fout("vd.txt", ios::app);
    if(!fout){
        cout<<"Loi mo file!";
        return;
    }
    cout<<"Nhap chuoi:"<<endl;
    while(true){
        cout<<"-->";getline(cin,st);
        if(st=="quit"){
            cout<<"Ket thuc!"<<endl;
            break;
        }
        fout<<st<<endl;
    }
    fout.close();
    done=true;
}
void task2(){
    while(!done){
        ifstream fin("vd.txt");
        if(!fin) return;
        int count=0;
        string line;
        while(getline(fin, line)){
            if(line!="quit") count++;
        }
        fin.close();
        cout<<"\nSo dong trong file: "<<count<<endl;
        this_thread::sleep_for(chrono::seconds(2));
    }
    remove("vd.txt");
    cout<<"Ket thuc task2!"<<endl;
}
int main(){
    thread t1(task1);
    thread t2(task2);
    t1.join();
    t2.join();
    return 0;
}