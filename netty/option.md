### socketChannel 

```
.option(ChannelOption.CONNECT_TIMEOUT_MILLIS,毫秒)
TCP_NODELAY true
```

#### serverSocketChannel

```
SO_BACKLOG 全连接队列最大数
SO_SNDBUF SO_RCVBUF窗口大小 
```

#### 共有

```
VM options:
bytebuf选项：
-Dio.netty.allocator.type=unpooled 非池化
-Dio.netty.noPreferDirect=true 使用堆内存
```

