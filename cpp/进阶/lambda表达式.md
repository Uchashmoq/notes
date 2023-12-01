## 形式

```c++
//[ capture ] ( params ) opt -> ret { body; };
//例：
[](double x )->double{int y = x ;return x - y;};
auto f = [](int x ){return x % 3 ==0;};
```

[] :表示不捕获任何变量
[=]：表示按值捕获变量
[&]：表示按引用捕获变量
[this]：值传递捕获当前的this

## 捕获

- `[var]`表示值传递方式捕获变量`var`

```cpp
int num = 100;
auto function = ([num]{
		std::cout << num << std::endl;
	}
);

function();
```

- `[&var]`表示**引用传递**捕捉变量`var`

```cpp
int num = 100;
auto function = ([&num]{
		num = 1000;
		std::cout << "num: " << num << std::endl;
	}
);

function();
```

- ```
  [=, &]
  ```

   

  拷贝与引用混合

  - `[=, &a, &b]`表示以引用传递的方式捕捉变量`a`和`b`，以值传递方式捕捉其它所有变量。

```cpp
int index = 1;
int num = 100;
auto function = ([=, &index, &num]{
		num = 1000;
		index = 2;
		std::cout << "index: "<< index << ", " 
            << "num: "<< num << std::endl;
	}
);

function();
```



## 选项

```c++
#include <iostream>
using namespace std;
int main()
{
	int a = 5;
	auto f = [=]()mutable{return a*=5;};//取消常量性
	cout << f() << endl;
	return 0;
}
```



