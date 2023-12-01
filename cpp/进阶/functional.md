## 三种bind

### bind1st

`bind1st(二元函数对象,x)`,  把x绑定到二元函数对象第一个参数，使其变成一个一元函数

```c++
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
struct Sum {
    int operator()(int a, int b) const {
        return a + b;
    }
};
int main() {
    // 创建一个 vector
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    // 使用 bind1st 将第一个参数绑定为 2
    auto addTwo = std::bind1st(Sum(), 2);
    // 使用 for_each 打印每个元素加上 2 的结果
    std::for_each(numbers.begin(), numbers.end(), addTwo);
    return 0;
}
```

### bind

std::bind 是C++标准库中的一个函数模板，用于创建函数对象，可以用来绑定参数、重排序参数或者固定部分参数。它提供了更灵活的方式来生成函数对象，通常与算法、线程、回调等场景结合使用。

```c++
#include <iostream>
#include <functional>
// 二元函数
int add(int a, int b) {
    return a + b;
}
int main() {
    // 使用 std::bind 绑定参数
    auto addFive = std::bind(add, 5, std::placeholders::_1);
    // 调用生成的函数对象
    std::cout << addFive(10) << std::endl;  // 输出 15
    return 0;
}
```

绑定成员函数

auto func=bind(&类::成员函数,&对象,placeholders::_1,placeholders::_2);

重排序参数：

auto func = std::bind(add, std::placeholders::_2, std::placeholders::_1);

固定参数值：

auto func = std::bind(add, 5, std::placeholders）

## function类

`function<返(参...)> func = 普通函数，仿函数，lambda`

```c++
int add(int a, int b) {
    return a + b;
}

// 函数对象
struct Multiply {
    int operator()(int a, int b) const {
        return a * b;
    }
};
int main() {
    // 使用 std::function 包装普通函数
    std::function<int(int, int)> addFunction = add;
    std::cout << "Addition: " << addFunction(3, 4) << std::endl;  // 输出 7

    // 使用 std::function 包装函数对象
    std::function<int(int, int)> multiplyFunction = Multiply();
    std::cout << "Multiplication: " << multiplyFunction(3, 4) << std::endl;  // 输出 12

    // 使用 Lambda 表达式
    std::function<int(int, int)> lambdaFunction = [](int a, int b) {
        return a / b;
    };
    std::cout << "Division: " << lambdaFunction(8, 2) << std::endl;  // 输出 4
    return 0;
}
```

## 内建函数对象

1. **std::plus<T>**: 加法仿函数。

   ```c++
   cppCopy code#include <functional>
   std::plus<int> add;  // 实例化一个int加法仿函数
   int result = add(3, 4);  // 结果为7
   ```

2. **std::minus<T>**: 减法仿函数。

   ```c++
   cppCopy code#include <functional>
   std::minus<int> subtract;  // 实例化一个int减法仿函数
   int result = subtract(7, 4);  // 结果为3
   ```

3. **std::multiplies<T>**: 乘法仿函数。

   ```c++
   cppCopy code#include <functional>
   std::multiplies<int> multiply;  // 实例化一个int乘法仿函数
   int result = multiply(3, 4);  // 结果为12
   ```

4. **std::divides<T>**: 除法仿函数。

   ```c++
   cppCopy code#include <functional>
   std::divides<int> divide;  // 实例化一个int除法仿函数
   int result = divide(12, 3);  // 结果为4
   ```

5. **std::modulus<T>**: 取模仿函数。

   ```c++
   cppCopy code#include <functional>
   std::modulus<int> modulus;  // 实例化一个int取模仿函数
   int result = modulus(13, 5);  // 结果为3
   ```

6. **std::negate<T>**: 取反仿函数。

   ```c++
   cppCopy code#include <functional>
   std::negate<int> negate;  // 实例化一个int取反仿函数
   int result = negate(7);  // 结果为-7
   ```



## 可变参

1.

实现函数可变参数的方法之一是使用 C++11 引入的可变参数模板。以下是一个简单的例子：

```c++
#include <iostream>
// 基本情况：当没有可变参数时，递归结束
void print() {
    std::cout << std::endl;
}
// 递归情况：处理第一个参数并递归调用 print 处理剩余的参数
template <typename T, typename... Args>
void print(T&& first, Args&&... args) {
    std::cout << std::forward<T>(first) << " ";
    print(std::forward<Args>(args)...);
}
int main() {
    print(1, "Hello", 3.14, "World");
    return 0;
}
```

在这个例子中，`print` 函数使用了可变参数模板。基本情况是当没有可变参数时，递归结束，打印换行符。递归情况是处理第一个参数并递归调用 `print` 处理剩余的参数。

当调用 `print(1, "Hello", 3.14, "World");` 时，它会递归展开参数，输出：`1 Hello 3.14 World`。

请注意，使用可变参数模板时，需要小心处理边界条件和递归调用，确保递归的正确终止。

2.

你可以使用模板和 `std::forward` 来实现一个函数 `foo`，该函数接受一个可调用对象（函数或函数对象）和一系列参数。以下是一个示例实现：

```c++
#include <iostream>
#include <functional>
template<typename Func, typename... Args>
decltype(auto) foo(Func&& func, Args&&... args) {
    return std::forward<Func>(func)(std::forward<Args>(args)...);
}
int main() {
    auto add = [](int a, int b) { return a + b; };
    int result = foo(add, 10, 20);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
```

在这个例子中，`foo` 函数使用了可变参数模板，允许它接受任意数量的参数。使用 `std::forward` 用于完美转发参数。`decltype(auto)` 用于推导返回类型，以保留被调用函数的返回类型。

在 `main` 函数中，我们定义了一个 lambda 函数 `add`，然后使用 `foo` 函数调用该 lambda 函数，并传递参数 10 和 20。得到的结果将会是 30。

你可以根据需要调整 `foo` 函数的参数和返回类型，使其适应不同的情况。