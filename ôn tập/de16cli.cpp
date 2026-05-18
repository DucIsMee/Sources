#include <bits/stdc++.h>
using namespace std;
list<int> a;

void nhap(int n){
    if(n<=0){cout<<"Ket thuc!";return;}
    for(int i=0;i<n;i++){
        int x;
        cout<<"Nhap phan tu thu "<<i+1<<": ";
        cin>>x;
        a.push_back(x);
    }
}