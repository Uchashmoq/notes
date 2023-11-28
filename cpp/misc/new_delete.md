```c++
using namespace std;
#include <iostream>
#include <string>
#include <cstring>

int main(){
    char *buf=new char[20];
    memset(buf,0,20);
    cin.get(buf,4);
    cout<<buf;
    delete[] buf;
    return 0;
}
```

