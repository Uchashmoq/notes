## 线程创建

```c++
using namespace std;
#include<thread>
#include<iostream>
void thread_func(string name){
    cout<<"start "<<name<<endl;
}
int main(){
    //线程函数传参
    thread th1(thread_func,"join");
    th1.join();
    //lambda表达式
    thread th2([](){cout<<"start lambda\n";});
    th2.join();

    thread th3(thread_func,"named detach");
    th3.detach();
    
    //匿名分离态线程
    thread (thread_func,"detach thread").detach();
    getchar();
}
```

## this_thread 类

```c++
#include <iostream>
#include <thread>
void printThreadId() {
    std::thread::id threadId = std::this_thread::get_id();
    std::cout << "Thread ID: " << threadId << std::endl;
}
int main() {
    // 在主线程中获取并打印线程 ID
    printThreadId();
    // 创建一个新线程并获取并打印其线程 ID
    std::thread secondThread(printThreadId);
    secondThread.join(); // 等待第二个线程完成
    return 0;
}
```

**this_thread是一个类，它有4个功能函数，具体如下：**

get_id	std::this_thread::get_id()	获取线程id
yield	std::this_thread::yield()	出让线程
sleep_for	std::this_thread::sleep_for(std::chrono::seconds(1));	暂停1秒
sleep_until	如下	一分钟后执行吗，如下

```c++
#include <iostream>
#include <chrono>
#include <thread>
int main() {
    // 获取当前时间点
    auto now = std::chrono::system_clock::now();
    // 设置休眠时间为当前时间点加上 3 秒
    auto wakeupTime = now + std::chrono::seconds(3);
    // 打印当前时间
    std::cout << "Current time: " << std::chrono::system_clock::to_time_t(now) << std::endl;
    // 休眠直至指定的时间点
    std::this_thread::sleep_until(wakeupTime);
    // 打印休眠后的时间
    auto afterSleep = std::chrono::system_clock::now();
    std::cout << "Woke up at: " << std::chrono::system_clock::to_time_t(afterSleep) << std::endl;
    return 0;
}
```

## 互斥锁

### mutex

mutex常用操作：

lock()：资源上锁
unlock()：解锁资源
trylock()：查看是否上锁，它有下列3种类情况：
（1）未上锁返回false，并锁住；
（2）其他线程已经上锁，返回true；
（3）同一个线程已经对它上锁，将会产生死锁。

### lock_guard

`std::lock_guard` 是 C++ 标准库提供的一个锁管理器，用于自动管理互斥量的锁。`std::lock_guard` 在构造时获取锁，在析构时释放锁，这样可以确保在作用域结束时互斥量被正确释放，从而避免因忘记释放锁而导致的死锁等问题。

以下是一个使用 `std::lock_guard` 的简单用例：

```c++
#include <iostream>
#include <mutex>
#include <thread>
std::mutex myMutex;
void criticalSection() {
    std::lock_guard<std::mutex> lock(myMutex);  // 在构造时获取锁
    // 在这里执行一些需要互斥的操作
    std::cout << "Thread ID " << std::this_thread::get_id() << " is in the critical section." << std::endl;
    // 在lock_guard的析构函数中自动释放锁，不需要手动调用 unlock
}
int main() {
    std::thread t1(criticalSection);
    std::thread t2(criticalSection);
    t1.join();
    t2.join();
    return 0;
}
```

### unique_lock

构造时获取锁，自动解锁

```c++
std::mutex myMutex;
void criticalSection() {
    std::unique_lock<std::mutex> lock(myMutex);  // 在构造时获取锁
    // 在这里执行一些需要互斥的操作
    std::cout << "Thread ID " << std::this_thread::get_id() << " is in the critical section." << std::endl;
    // 不需要手动释放锁，unique_lock 在析构时会自动释放锁
}
```

构造时不获得锁，手动加锁

```c++
std::mutex myMutex;
void criticalSection() {
    std::unique_lock<std::mutex> lock(myMutex, std::defer_lock);  // 不在构造时获取锁
    // 在这里执行一些不需要互斥的操作
    lock.lock();  // 手动获取锁
    // 在这里执行一些需要互斥的操作
    std::cout << "Thread ID " << std::this_thread::get_id() << " is in the critical section." << std::endl;
    lock.unlock();  // 手动释放锁
}
```

## 条件量

### condition_variable

`std::condition_variable` 是 C++ 标准库提供的用于多线程间同步的机制，通常与 `std::mutex` 一起使用。它用于等待某个条件变为真，或者通知其他线程条件已经满足。

下面是一个简单的例子，演示了如何使用 `std::condition_variable`：

#### wait

```c++
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

std::mutex myMutex;
std::condition_variable cv;
bool isDataReady = false;

void dataProducer() {
    // 模拟一些计算工作
    std::this_thread::sleep_for(std::chrono::seconds(2));
    // 准备数据
    {
        std::lock_guard<std::mutex> lock(myMutex);
        //先获得锁
        isDataReady = true;
    }
    // 通知等待的线程
    cv.notify_one();
}

void dataConsumer() {
    std::unique_lock<std::mutex> lock(myMutex);
    // 等待条件满足
    cv.wait(lock, [] { return isDataReady; });
    // 处理数据
    std::cout << "Data is ready for processing." << std::endl;
}
int main() {
    // 启动数据生产者线程
    std::thread producerThread(dataProducer);
    // 启动数据消费者线程
    std::thread consumerThread(dataConsumer);
    // 等待线程结束
    producerThread.join();
    consumerThread.join();
    return 0;
}
```

在这个例子中，`dataProducer` 函数模拟了一些计算工作，然后设置了一个标志 `isDataReady` 表示数据已经准备好。接着，通过调用 `cv.notify_one()` 通知等待的线程条件已经满足。

`dataConsumer` 函数中，首先使用 `std::unique_lock` 对互斥量进行上锁，然后调用 `cv.wait` 来等待条件满足。`cv.wait` 会自动释放互斥量，并在等待时阻塞线程。当其他线程调用 `cv.notify_one()` 时，被阻塞的线程将被唤醒，重新获得互斥量，并检查条件是否满足。在这个例子中，一旦 `isDataReady` 变为 `true`，线程将继续执行，输出一条消息表示数据准备好。这种使用方式允许线程在等待条件时阻塞，并在条件满足时被唤醒，从而实现了线程之间的协调。

```c++
#include<string>
#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;

mutex msg_lock;
bool ready = false;
condition_variable cv;

void producer(string *msg){
    {
        //3. 出让后获得锁
        unique_lock<mutex> lck(msg_lock);
        cin>>(*msg);
        ready=true;
    }
    //使锁回归
    cv.notify_all();
}
void comsumer(string *msg){
    //1 .先获得锁
    unique_lock<mutex> lck(msg_lock);
    //2 .出让锁，等待notify再回归
    cv.wait(lck , [](){return ready;});
    cout<<"receive : "<<(*msg)<<endl;
}
int main(){
    string s;
    thread pth(producer,&s);
    thread cth(comsumer,&s);
    pth.join();
    cth.join();
}
```

#### wait_for

```c++
if (cv.wait_for(lck, chrono::seconds(3), [] { return ready; })) {
        cout << "Received: " << (*msg) << endl;
    } else {
        cout << "Timeout reached. No data received." << endl;
    }
```

#### wait_until

```c++
auto timeout = chrono::steady_clock::now() + chrono::seconds(5);
    // 等待条件满足或者超时
    if (cv.wait_until(lck, timeout, [] { return ready; })) {
        cout << "Received: " << (*msg) << endl;
    } else {
        cout << "Timeout reached. No data received." << endl;
    }
```

### conditional_variable_any

`std::condition_variable_any` 是 C++ 标准库提供的另一种条件变量，它可以与任何可上锁的类型一起使用，而不仅仅是 `std::mutex`。这在某些情况下可能是有用的，例如，当你使用自定义的互斥量时。

以下是一个简单的例子，演示了 `std::condition_variable_any` 的用法：

```c++
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class CustomMutex {
public:
    void lock() {
        // 自定义上锁逻辑
        cout << "CustomMutex locked" << endl;
    }
    void unlock() {
        // 自定义解锁逻辑
        cout << "CustomMutex unlocked" << endl;
    }
    // 其他可能需要实现的互斥量接口函数
};

CustomMutex myMutex;
condition_variable_any cv;
bool ready = false;

void producer(string *msg) {
    {
        lock_guard<CustomMutex> lock(myMutex);
        cin >> (*msg);
        ready = true;
    }
    cv.notify_all();
}

void consumer(string *msg) {
    unique_lock<CustomMutex> lock(myMutex);

    cv.wait(lock, [] { return ready; });

    cout << "Received: " << (*msg) << endl;
}

int main() {
    string s;
    thread pth(producer, &s);
    thread cth(consumer, &s);
    pth.join();
    cth.join();

    return 0;
}
```

在这个例子中，`myMutex` 是一个自定义的互斥量类型，它实现了 `lock()` 和 `unlock()` 函数，使其可以与 `std::condition_variable_any` 一起使用。注意，在使用 `condition_variable_any` 时，你需要使用 `unique_lock`，而不是 `lock_guard`。

总的来说，`std::condition_variable_any` 是一种通用的条件变量，可以搭配任何支持上锁的类型使用，而不仅仅是标准库提供的 `std::mutex`。

