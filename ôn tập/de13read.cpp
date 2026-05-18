#include <iostream>
#include <fstream>
#include <thread>
#include <iomanip>
using namespace std;
void docFile(){
    ifstream fin("vd.txt");
    if(!fin){
        cout<<"Loi mo file!";
        return;
    }
    char c;
    while(fin.get(c)){
        if(c!='#' && c!='\n') {
            cout<<"Ky tu doc duoc: "<<c<<" HEX: "<<hex<<(int)(unsigned char)c<<dec<<endl;
        }
    }
    fin.close();
}
int main(){
    thread t(docFile);
    t.join();
    return 0;
}