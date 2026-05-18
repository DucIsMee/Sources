#include <iostream>
#include <fstream>
#include <thread>
using namespace std;

void ghiFile(){
    ofstream fout("vd.txt",ios::trunc);
    if(!fout){
        cout<<"Loi mo file!";
        return;
    }
    char c;
    while(true){
        cout<<"Nhap ky tu: ";
        cin >> c;
        if(c=='#'){
            cout<<"Ket thuc!"<<endl;
            break;
        }
        fout << c << endl;
    }
    cout<<"Da xong ghi file"<<endl;
    fout.close();
}
void docFile(){
    ifstream fin("vd.txt");
    if(!fin){
        cout<<"Loi mo file!";
        return;
    }
    char c;
    while(fin.get(c)){
        if(c=='#') break;
        cout<<"Ky tu doc duoc: "<<c<<" HEX: "<<hex<<(int)(unsigned char)c<<dec<<endl;
    }
    fin.close();
    this_thread::sleep_for(chrono::milliseconds(500));
}
int main(){
    thread t1(ghiFile);
    thread t2(docFile);
    t1.join();
    t2.join();
}