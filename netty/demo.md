## 回显服务器(DatagramChannel)

```java
public static void main(String[] args) throws Exception {
		int port=12345;
		// 配置事件循环器
		EventLoopGroup group = new NioEventLoopGroup();
		try {
			// 启动NIO服务的引导程序类
			Bootstrap b = new Bootstrap();
			b.group(group) // 设置EventLoopGroup
			.channel(NioDatagramChannel.class) // 指明新的Channel的类型
			.option(ChannelOption.SO_BROADCAST, true) // 设置的Channel的一些选项
			.handler(new DatagramChannelEchoServerHandler()); // 指定ChannelHandler
			// 绑定端口
			ChannelFuture f = b.bind(port).sync();
			System.out.println("DatagramChannelEchoServer已启动，端口：" + port);
			// 等待服务器 socket 关闭 。
			// 在这个例子中，这不会发生，但你可以优雅地关闭你的服务器。
			f.channel().closeFuture().sync();
		} finally {
			// 优雅的关闭
			group.shutdownGracefully();
		}
	}

public class DatagramChannelEchoServerHandler extends ChannelInboundHandlerAdapter {
	@Override
	public void channelRead(ChannelHandlerContext ctx, Object msg) {
		// 消息转为DatagramPacket类型
		DatagramPacket packet = (DatagramPacket)msg;
		System.out.println(packet.sender() + " -> Server :" + msg);
		// 构建新DatagramPacket   					源内容			源地址
		DatagramPacket data = new DatagramPacket(packet.content(), packet.sender());
		ctx.writeAndFlush(data);
	}
	@Override
	public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) {
		// 当出现异常就关闭连接
		cause.printStackTrace();
		ctx.close();
	}
}
```

在 Netty 中，`DatagramPacket` 类主要用于处理 UDP 数据报（Datagram）。UDP 是一种无连接的协议，`DatagramPacket` 封装了 UDP 数据报的内容和相关的信息。以下是 `DatagramPacket` 的一些主要用法：

1. **创建 DatagramPacket 对象**:

   ```java
   InetSocketAddress recipient = new InetSocketAddress("127.0.0.1", 8080);
   ByteBuf data = Unpooled.copiedBuffer("Hello, Netty!", CharsetUtil.UTF_8);
   DatagramPacket datagramPacket = new DatagramPacket(data, recipient);
   ```

   这段代码创建了一个 `DatagramPacket` 对象，将 "Hello, Netty!" 字符串数据放入 `ByteBuf` 中，并指定了接收方的地址信息（InetSocketAddress）。

2. **获取数据**:

   ```java
   ByteBuf receivedData = datagramPacket.content();
   byte[] byteArray = new byte[receivedData.readableBytes()];
   receivedData.readBytes(byteArray);
   String receivedMessage = new String(byteArray, CharsetUtil.UTF_8);
   ```

   使用 `content()` 方法获取 `ByteBuf`，然后可以通过不同的方法从 `ByteBuf` 中读取数据。在这个例子中，将 `ByteBuf` 中的数据读取到一个字节数组，并转换为字符串。

3. **获取发送方和接收方信息**:

   ```java
   InetSocketAddress senderAddress = datagramPacket.sender();
   InetSocketAddress recipientAddress = datagramPacket.recipient();
   ```

   使用 `sender()` 方法可以获取发送方的地址信息，而 `recipient()` 方法可以获取接收方的地址信息。

4. **修改接收方地址信息**:

   ```java
   datagramPacket.setRecipient(new InetSocketAddress("localhost", 9090));
   ```

   可以使用 `setRecipient()` 方法修改 `DatagramPacket` 的接收方地址信息。

5. **释放资源**:

   ```java
   datagramPacket.release();
   ```

   在使用完 `DatagramPacket` 后，需要手动释放资源，以避免内存泄漏。

这些是 `DatagramPacket` 主要的用法，它提供了一种方便的方式来处理 UDP 数据报，让开发者可以更容易地进行 UDP 通信的操作。

## 回显客户端

```java
public final class DatagramChannelEchoClient {
	public static void main(String[] args) throws Exception {
		String targetHost = "127.0.0.1";
		int targetPort=12345;
		int port = 9999;
		// 配置客户端
		EventLoopGroup group = new NioEventLoopGroup();
		try {
			Bootstrap b = new Bootstrap();
			b.group(group)
			.channel(NioDatagramChannel.class)
			.option(ChannelOption.SO_BROADCAST, true)
			.handler(new DatagramChannelEchoClientHandler());

			// 绑定端口
			ChannelFuture f = b.bind(port).sync();

			System.out.println("DatagramChannelEchoClient已启动，端口：" + port);
			Channel channel = f.channel();
			ByteBuffer writeBuffer = ByteBuffer.allocate(32);
            
			try (BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in))) {
				String userInput;
				while ((userInput = stdIn.readLine()) != null) {
					writeBuffer.put(userInput.getBytes());
					writeBuffer.flip();
					writeBuffer.rewind();
					// 转为ByteBuf
					ByteBuf buf = Unpooled.copiedBuffer(writeBuffer);
					// 写消息到管道
					// 消息封装为DatagramPacket类型
					channel.writeAndFlush(
							new DatagramPacket(buf, 
							new InetSocketAddress(targetHost, targetPort))
					);
					// 清理缓冲区
					writeBuffer.clear();
				}
			} catch (UnknownHostException e) {
				System.err.println("不明主机，主机名为： " + targetHost);
				System.exit(1);
			} catch (IOException e) {
				System.err.println("不能从主机中获取I/O，主机名为：" + targetHost);
				System.exit(1);
			}
		} finally {
			// 优雅的关闭
			group.shutdownGracefully();
		}
	}
}

public class DatagramChannelEchoClientHandler extends ChannelInboundHandlerAdapter {
	@Override
	public void channelRead(ChannelHandlerContext ctx, Object msg) {
		
		// 从管道读消息
		DatagramPacket packet = (DatagramPacket) msg; // 转为DatagramPacket类型
		String m = packet.content().toString(CharsetUtil.UTF_8);  // 转为字符串
		System.out.println( "echo :" + m);
	}

	@Override
	public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) {

		// 当出现异常就关闭连接
		cause.printStackTrace();
		ctx.close();
	}
}
```



## Reactor模式服务器