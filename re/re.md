### reverse_3

```c
int __cdecl main_0(int argc, const char **argv, const char **envp)
{
  size_t v3; // eax
  const char *v4; // eax
  size_t v5; // eax
  char v7; // [esp+0h] [ebp-188h]
  char v8; // [esp+0h] [ebp-188h]
  signed int j; // [esp+DCh] [ebp-ACh]
  int i; // [esp+E8h] [ebp-A0h]
  signed int v11; // [esp+E8h] [ebp-A0h]
  char Destination[108]; // [esp+F4h] [ebp-94h] BYREF
  char Str[28]; // [esp+160h] [ebp-28h] BYREF
  char v14[8]; // [esp+17Ch] [ebp-Ch] BYREF

  for ( i = 0; i < 100; ++i )
  {
    if ( (unsigned int)i >= 0x64 )
      j____report_rangecheckfailure();
    Destination[i] = 0;
  }
  sub_41132F("please enter the flag:", v7);
  sub_411375("%20s", (char)Str);
  v3 = j_strlen(Str);
  v4 = (const char *)sub_4110BE(Str, v3, v14);//base64加密
  strncpy(Destination, v4, 0x28u);
  v11 = j_strlen(Destination);
  for ( j = 0; j < v11; ++j )
    Destination[j] += j;//每一位字符加上索引
  v5 = j_strlen(Destination);
  if ( !strncmp(Destination, Str2, v5) )
    sub_41132F("rigth flag!\n", v8);
  else
    sub_41132F("wrong flag!\n", v8);
  return 0;
}
```

先对每一位减，再base64解密

### 不一样的flag

```c
int __cdecl __noreturn main(int argc, const char **argv, const char **envp)
{
  char v3[29]; // [esp+17h] [ebp-35h] BYREF
  int v4; // [esp+34h] [ebp-18h]
  int v5; // [esp+38h] [ebp-14h] BYREF
  int i; // [esp+3Ch] [ebp-10h]
  _BYTE v7[12]; // [esp+40h] [ebp-Ch] BYREF

  __main();
  v4 = 0;
  strcpy(v3, "*11110100001010000101111#");
  /*
  *1111
  01000
  01010
  00010
  1111#
 走迷宫
  */
  while ( 1 )
  {
    puts("you can choose one action to execute");
    puts("1 up");
    puts("2 down");
    puts("3 left");
    printf("4 right\n:");
    scanf("%d", &v5);
    if ( v5 == 2 ){
      ++*(_DWORD *)&v3[25];//下1
    }else if ( v5 > 2 ){
      if ( v5 == 3 ){
        --v4;//上
      }else{
        if ( v5 != 4 )
LABEL_13:
          exit(1);
        ++v4;
      }
    }
    else
    {
      if ( v5 != 1 )
        goto LABEL_13;
      --*(_DWORD *)&v3[25];
    }
    for ( i = 0; i <= 1; ++i )
    {
      if ( *(int *)&v3[4 * i + 25] < 0 || *(int *)&v3[4 * i + 25] > 4 )
        exit(1);
    }
    if ( v7[5 * *(_DWORD *)&v3[25] - 41 + v4] == '1' )
      exit(1);
    if ( v7[5 * *(_DWORD *)&v3[25] - 41 + v4] == '#' )
    {
      puts("\nok, the order you enter is the flag!");
      exit(0);
    }
  }
}
```

### Java逆向

```java
import java.util.ArrayList;
import java.util.Scanner;

public class Reverse {
    public Reverse() {
    }

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        System.out.println("Please input the flag ：");
        String str = s.next();
        System.out.println("Your input is ：");
        System.out.println(str);
        char[] stringArr = str.toCharArray();
        Encrypt(stringArr);
    }

    public static void Encrypt(char[] arr) {
        ArrayList<Integer> Resultlist = new ArrayList();

        for(int i = 0; i < arr.length; ++i) {
            int result = arr[i] + 64 ^ 32;
            Resultlist.add(result);
        }

        int[] KEY = new int[]{180, 136, 137, 147, 191, 137, 147, 191, 148, 136, 133, 191, 134, 140, 129, 135, 191, 65};
        ArrayList<Integer> KEYList = new ArrayList();

        for(int j = 0; j < KEY.length; ++j) {
            KEYList.add(KEY[j]);
        }
        System.out.println("Result:");
        if (Resultlist.equals(KEYList)) {
            System.out.println("Congratulations！");
        } else {
            System.err.println("Error！");
        }
    }
}

```

解题程序

```c++
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
```

### luck_guy

分析执行顺序 case4->5->1

```c
unsigned __int64 get_flag()
{
  unsigned int v0; // eax
  int i; // [rsp+4h] [rbp-3Ch]
  int j; // [rsp+8h] [rbp-38h]
  __int64 s; // [rsp+10h] [rbp-30h] BYREF
  char v5; // [rsp+18h] [rbp-28h]
  unsigned __int64 v6; // [rsp+38h] [rbp-8h]

  v6 = __readfsqword(0x28u);
  v0 = time(0LL);
  srand(v0);
  for ( i = 0; i <= 4; ++i )
  {
    switch ( rand() % 200 )
    {
      case 1:
        puts("OK, it's flag:");
        memset(&s, 0, 0x28uLL);
        strcat((char *)&s, GXY);                // GXY{do_not_
        strcat((char *)&s, &f2);
        printf("%s", (const char *)&s);
        break;
      case 2:
        printf("Solar not like you");
        break;
      case 3:
        printf("Solar want a girlfriend");
        break;
      case 4:
        s = 0x7F666F6067756369LL;
        v5 = 0;
        strcat(&f2, (const char *)&s);
        break;
      case 5:
        for ( j = 0; j <= 7; ++j )
        {
          if ( j % 2 == 1 )
            *(&f2 + j) -= 2;
          else
            --*(&f2 + j);
        }
        break;
      default:
        puts("emmm,you can't find flag 23333");
        break;
    }
  }
  return __readfsqword(0x28u) ^ v6;
}
```

```c
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
```

