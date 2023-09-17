### 创建一个窗口程序

```c++
#include<Windows.h>                                                                 
int WINAPI WinMain(
    HINSTANCE hInstance,//本程序对象
    HINSTANCE hPrevInstance, //上一个程序对象
    LPSTR lpCmdLine, //命令行参数
    int nCmdShow//显示模式
) {            
    MessageBox(
        NULL//窗口所有者
        ,L"context",//内容
        L"title",//标题
        MB_ICONINFORMATION//窗口模式
    );

    return 0;
}
```

