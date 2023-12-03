## 可变参

```c
#include <stdio.h>
#include <stdarg.h>

// 可变参数函数，计算不定数量的整数之和
int sum(int count, ...) {
    int total = 0;
    
    va_list args; // 定义可变参数列表
    va_start(args, count); // 初始化可变参数列表

    for (int i = 0; i < count; i++) {
        int num = va_arg(args, int); // 从可变参数列表中获取参数
        total += num;
    }

    va_end(args); // 结束可变参数列表

    return total;
}

int main() {
    int result = sum(5, 1, 2, 3, 4, 5);
    printf("Sum: %d\n", result);

    return 0;
}
```

## TCP套接字基础

### 函数

```c
int bind(sockfd,(struct sockaddr*)&sa,sizeof(sa)); 
/*
0成功，1错误
sin_addr.s_addr=htonl(INADDR_ANY) port=htons(0) 内核选择
*/
int connect(sockfd,(struct sockaddr*)&sa,sizeof(sa));

#include<unistd.h>
pid_t id=fork();
/*
父进程获得子进程id，子进程 id=0,getppid() 获得父进程id
创建子进程sockfd引用计数加一，要先在父进程关闭
*/

int execl(可执行文件路径,const char *arg0...(char*)0);

int getsockname(sockfd,(struct sockaddr*)&sa,socklen_t *addrlen);//获取套接字本地地址
int getpeername(sockfd,(struct sockaddr*)&sa,socklen_t *addrlen);//获取套接字远程地址,fork出的子进程中获取对端地址    
```

### 封装函数readn ,writen, readline函数

```c
ssize_t writen(int fd,const char* vptr,size_t n){
    size_t nleft=n;
    ssize_t nwritten;
    const char* ptr=vptr;
    while(nleft>0){
        //发送失败
        if((nwritten=write(fd , ptr , nleft))<=0){
            if(nwritten<0 && errno==EINTR) nwritten=0;//被信号中断，再发一次
            else return -1;// 0,-1连接被强行中断
        }
        //分片发
        nleft-=nwritten;
        ptr+=nwritten;
    }
}
```

## 信号

```c
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

typedef void Sigfunc(int);

Sigfunc * registerSigfunc(int signo,Sigfunc *func){
    //
    struct sigaction act,oact;
    //清空掩码集
    sigisemptyset(&act.sa_mask);
    act.sa_handler=func;
    //中断系统调用,SA_RESTART
    act.sa_flags=SA_INTERRUPT;
    if(sigaction(signo,&act,&oact)<0) return SIG_ERR;
    //返回旧的handler
    return oact.sa_handler;
}

void sigtstp_func(int signo){
    printf("\ncatch %d\n",signo);
}
void sigint_func(int signo){
    printf("\nctrl+c ,catch %d\n",signo);
    exit(0);
}

int main(){
    registerSigfunc(SIGTSTP,sigtstp_func);
    registerSigfunc(SIGINT,sigint_func);
    int i;
    for(i=0;i<100;++i){
        sleep(1);
        printf("**%d**\n",i);
    }
}

```

同名信号排队执行，不同名信号可以同时执行，如果加入掩码就排队

### struct sigaction

下面是 `sigaction` 结构体的主要成员变量以及它们的作用：

```c
struct sigaction {
    void (*sa_handler)(int);      // 指定信号处理函数的地址
    sigset_t sa_mask;             // 信号屏蔽集，在信号处理函数执行期间阻塞的信号
    int sa_flags;                  // 用于设置一些标志，例如 SA_RESTART，SA_SIGINFO 等
    void (*sa_sigaction)(int, siginfo_t *, void *);  // 用于传递更多信息的信号处理函数（与 sa_handler 二选一）
};
```

这里是每个成员变量的作用：

1. **`sa_handler`：**
   - 类型：`void (*sa_handler)(int)`
   - 作用：指定处理信号的函数的地址。当该函数被调用时，它接收一个整数参数，表示信号的编号。
2. **`sa_mask`：**
   - 类型：`sigset_t`
   - 作用：指定在信号处理函数执行期间需要被阻塞的信号集。被阻塞的信号将在信号处理函数执行期间暂时屏蔽，防止它们再次触发。
3. **`sa_flags`：**
   - 类型：`int`
   - 作用：用于设置一些标志，影响信号处理的行为。常见的标志包括 `SA_RESTART`（指定在被中断的系统调用可以自动重启）、`SA_SIGINFO`（使用 `sa_sigaction` 而不是 `sa_handler` 处理信号）等。
4. **`sa_sigaction`：**
   - 类型：`void (*sa_sigaction)(int, siginfo_t *, void *)`
   - 作用：与 `sa_handler` 二选一，用于传递更多关于信号的信息。当设置了 `SA_SIGINFO` 标志时，`sa_sigaction` 被调用，它接收三个参数：信号编号、`siginfo_t` 结构体（提供有关信号的更多信息）和上下文信息。

使用 `sigaction` 结构体可以更灵活地控制信号的处理方式，以及在信号处理过程中的一些行为。

### sa_mask

使用 `sa_mask` 时，可以使用一系列相关的函数来操作信号集，例如：

- `sigemptyset(sigset_t *set)`: 清空信号集，将所有信号从集合中移除。
- `sigfillset(sigset_t *set)`: 将所有信号添加到信号集中。
- `sigaddset(sigset_t *set, int signo)`: 将指定的信号添加到信号集中。
- `sigdelset(sigset_t *set, int signo)`: 从信号集中移除指定的信号。
- `sigismember(const sigset_t *set, int signo)`: 检查指定的信号是否在信号集中。
