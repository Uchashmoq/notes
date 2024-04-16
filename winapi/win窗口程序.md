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

```c++
#include<windows.h>
//消息处理函数
LRESULT CALLBACK proc1(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lparam) {
	return DefWindowProc(hWnd, msgID, wParam, lparam);
}

int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR LpCmd, int nCmdShow) {
	WNDCLASS wc = { 0 };

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;
	wc.lpfnWndProc = proc1;
	wc.lpszClassName = L"test";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);
	//在内存创建窗口
	HWND wnd1 = CreateWindow(
		L"test", L"window",
		WS_OVERLAPPEDWINDOW,
		100, 100,/*显示位置*/
		500, 500,/*尺寸*/
		NULL /*父窗口*/, NULL/*菜单*/,
		hIns, NULL
	);
	ShowWindow(wnd1, SW_SHOW);
	UpdateWindow(wnd1);

	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0)) {
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);
	}
	return 0;
}
```

