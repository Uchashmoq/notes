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
    //               新   旧
    struct sigaction act,oact;
    
    sigisemptyset(&act.sa_mask);
    //将sigint信号添加进掩码集，遇到sigint时不会中断
    sigaddset(&act.sa_mask,SIGINT);
    act.sa_handler=func;
    //不恢复系统调用
    act.sa_flags=SA_INTERRUPT;
    
    if(sigaction(signo,&act,&oact)<0) return SIG_ERR;
    return oact.sa_handler;
}

void sigtstp_func(int signo){
    printf("\nctrl+z ,catch %d\n",signo);
    int i;
    for(i=0;i<5;++i){
        sleep(1);
        puts("Z");
    }
}
void sigint_func(int signo){
    printf("\nctrl+c ,catch %d\n",signo);
    int i;
    for(i=0;i<5;++i){
        sleep(1);
        puts("C");
    }
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

同名信号排队执行，不同名信号可以打断，如果加入掩码就排队

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

### 处理SIGCHLD

```c
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void sig_child(int signo){
    pid_t pid;
    int stat;
    pid=wait(&stat);//等待任意子进程结束
    printf("%d exit with status %d\n",pid,stat);
}

int main(){
    //子进程结束后父进程将会收到SIGCHLD信号
    signal(SIGCHLD,sig_child);
    pid_t pid;
    pid=fork();
    if(pid==0){
        //子进程打印循环后结束
        printf("child pid : %d\n",getpid());
        int i;
        for(i=1;i<=4;++i){
            printf("/%d/\n",i);
            sleep(1);
        }
        exit(0);
    }else{
        int i;
        for(i=1;i<=100;++i){
            printf("**%d**\n",i);
            sleep(1);
        }
    }
}
```

### 恢复系统调用

`慢系统调用`如accept会在信号函数返回时返回 EINTR宏，需要把 `sa_flags` 设置为`SA_RESTART`，或继续循环

### wait , waitpid 函数

`pid_t wait(&状态)`

`pid_t wait(pid,&状态,选项)` , pid=-1等待第一个，选项 `WNOHANG`不阻塞

#### 检查状态

1. **`WIFEXITED(status)`：**
   - 用于检查子进程是否正常退出。如果子进程正常结束（即没有被信号终止），`WIFEXITED(status)` 将为真。
   - 具体而言，如果 `status` 表示子进程正常结束，`WIFEXITED(status)` 将返回一个非零值，表示子进程已经成功退出。
2. **`WIFSIGNALED(status)`：**
   - 用于检查子进程是否由于信号而终止。如果子进程是因为收到一个信号而结束的，`WIFSIGNALED(status)` 将为真。
   - 具体而言，如果 `status` 表示子进程由于收到信号而终止，`WIFSIGNALED(status)` 将返回一个非零值，表示子进程是由于信号而非正常退出的。

### 问题:wait只调用一次 

多个子进程同时结束可能导致父进程只执行一次子进程处理函数，造成其他子进程僵死

```c
while((pid=waitpid(-1 , &stat , WNOHANG))> 0 ){
    printf("%d terminated\n",pid);
}
```

### 处理SIGPIPE

客户端可能会收到来自服务端的RST（Reset）信号的情况有一些，其中一些典型的场景包括：

1. **连接被服务端主动关闭：** 如果服务端主动关闭了连接，并且此时客户端尝试在已关闭的连接上发送数据，服务端会发送RST信号作为响应。这表明服务端不再接受来自该客户端的数据。
2. **服务端崩溃或异常：** 如果服务端发生了崩溃或其他异常情况，操作系统可能会发送RST信号来终止与该客户端的连接。
3. **服务端处理请求异常：** 在某些情况下，服务端可能会在处理客户端请求时发生异常，导致连接被中断，并向客户端发送RST信号。
4. **防火墙或网络设备的干预：** 防火墙或其他网络设备可能会在网络层面上介入，导致连接被重置。这可能是由于网络故障、拦截恶意流量或其他安全策略。
5. **超时或心跳机制：** 在一些情况下，服务端可能会设置连接超时或心跳机制，如果客户端在规定的时间内未发送或接收数据，服务端可能会发送RST信号来关闭连接。

**向收到RST的套接字写入内容会收到 SIGPIPE信号，写操作返回 EPIPE错误**

```c
signal(SIGPIPE, SIG_IGN);//忽略SIGPIPE
```

## select  <sys/types.h>

`select(最大符+1,&readset,&writeset,&exceptset,const struct timeval *timeout)`-> 就绪数，0超时，-1被信号中断

### 就绪条件

1. 可读： 读缓冲区数据多于接收区缓冲区低水位标记的当前大小；收到FIN，操作套接字返回0；监听套接字且已完成连接数>0;套接字错误，操作返回-1

2. 可写：写缓冲区数据多于接收区缓冲区低水位标记的当前大小；套接字关闭，操作产生SIGPIPE；非阻塞connect成功或失败；套接字错误，操作返回-1

   

   



