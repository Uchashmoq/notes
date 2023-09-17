### pipline

```java
 nioSocketChannel.pipeline()
                               	.addLast("in1",new ChannelInboundHandlerAdapter(){
                                    @Override
                                    public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
                                        ByteBuf buf=(ByteBuf)msg;
                                        String s=buf.toString(Charset.forName("GBK"));
                                        System.out.println("接收到字符串"+s);
                                        super.channelRead(ctx, s);
                                    }
                                })
                                .addLast("h2",new ChannelInboundHandlerAdapter(){
                                    @Override
                                    public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
                                        String s=(String)msg;
                                        System.out.println("开始处理字符串");
                                        nioSocketChannel.writeAndFlush(ctx.alloc().buffer().writeBytes((s+"哈哈嗨").getBytes(Charset.forName("GBK"))));
                                    }
                                })
                                .addLast("out1",new ChannelOutboundHandlerAdapter(){
                                    @Override
                                    public void write(ChannelHandlerContext ctx, Object msg, ChannelPromise promise) throws Exception {//从尾部向前
                                        System.out.println("已发送");
                                        super.write(ctx, msg, promise);
                                    }
                                });
```

### EmbeddedChannel

```java
  ChannelInboundHandlerAdapter in1 = new ChannelInboundHandlerAdapter(){
            @Override
            public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
                ByteBuf buf=(ByteBuf)msg;
                String s=buf.toString(Charset.forName("GBK"));
                System.out.println(s);
                super.channelRead(ctx, msg);
            }
        };
		//向通道添加adapter
        EmbeddedChannel ec=new EmbeddedChannel(in1);
		//向通道写入数据
        ec.writeInbound(ByteBufAllocator.DEFAULT.buffer().writeBytes("nihao".getBytes()));

```

