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

