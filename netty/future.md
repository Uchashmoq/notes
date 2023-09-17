### ChannelFuture

#### 调用connect()

```java
ChannelFuture cft = new Bootstrap()
                .group(eventLoopGroup)
                .channel(NioSocketChannel.class)
                .handler(new ChannelInitializer<NioSocketChannel>() {
                    @Override
                    protected void initChannel(NioSocketChannel chan) throws Exception {
                        chan.pipeline().addLast(new StringEncoder());
                    }
                }).connect(new InetSocketAddress(12346));//异步
//connect异步，调用后会返回 ChannelFuture对象，需要用sync()或addListener()待连接成功后再拿出channel

cft.addListener(new ChannelFutureListener() {
            @Override
            public void operationComplete(ChannelFuture channelFuture) throws Exception{
                //连接成功后执行
                channelFuture.channel().writeAndFlush("执行回调对象");
            }
        });
```

#### channel调用closeFuture()

用于处理channel关闭以后的事务

```java
 ChannelFuture closeFuture = channel.closeFuture();//获得通道关闭后对象
        closeFuture.addListener(new ChannelFutureListener() {//指定关闭后操作
            @Override
            public void operationComplete(ChannelFuture channelFuture) throws Exception {
                System.out.println("关闭后的操作");
                eventLoopGroup.shutdownGracefully();//关闭group
            }
        });

        channel.close();
```

### Future

#### JDK的Future

```java
 ExecutorService pool= Executors.newFixedThreadPool(3);

        Callable<String> task =new Callable<String>() {
            @Override
            public String call() throws Exception {
                Thread.sleep(2*1000);
                return "Result";
            }
        };
//向线程池提交Callable对象后会返回future对象，get阻塞直到线程结束
        Future<String> future = pool.submit(task);//提交callable对象
        System.out.println(future.get());
        pool.close();
```

#### Netty的Future

```java
 NioEventLoopGroup group = new NioEventLoopGroup();

        Callable<String> task =new Callable<String>() {
            @Override
            public String call() throws Exception {
                Thread.sleep(2*1000);
                return "Result";
            }
        };

        Future<String> future = group.submit(task);
       // System.out.println(future.get());
		//线程后结束执行回调方法
        future.addListener(new GenericFutureListener<Future<? super String>>() {
            @Override                                                                                   
            //刚才外面的future
            public void operationComplete(Future<? super String> future) throws Exception {
                System.out.println(future.getNow());
            }
        });

        group.shutdownGracefully();
```

![future方法](C:\笔记\netty\future方法.png)

### Promise

```java
		
		NioEventLoopGroup group = new NioEventLoopGroup();
        DefaultPromise<Integer> promise=new DefaultPromise(group.next());

        new Thread(()->{
            try {
                Thread.sleep(1000);
                promise.setSuccess(999);//设置结果，promise.get()结束阻塞
            }catch (Exception e){
                promise.setFailure(e);
            }
        }).start();

        System.out.println(promise.get());
        group.shutdownGracefully();
```



