#include<iostream>
using namespace std;
int main(){
    int key[]={180, 136, 137, 147, 191, 137, 147, 191, 148, 136, 133, 191, 134, 140, 129, 135, 191, 65};
    char txt[19]={0};
    for(int i=0;i<18;++i){
        txt[i]=(char)((key[i]^32)-64);
    }
    printf("%s",txt);
}