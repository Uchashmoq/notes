#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
int main(){
    int64_t s=0x7F666F6067756369LL;
    char f1[]="GXY{do_not_"  ,f2[64]={0};
    strcat(f2,(char*)&s);
    int j;
    for ( j = 0; j <= 7; ++j ){
      if ( j % 2 == 1 )
        *(f2 + j) -= 2;
      else
        --*(f2 + j);
    }
    printf("%s%s",f1,f2);
}