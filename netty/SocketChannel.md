## SocketChannel

#### 非阻塞套接字通道

##### 无限循环服务器

```java
public static void main(String[] args) throws Exception{
		ByteBuffer buffer=ByteBuffer.allocate(256);
		ServerSocketChannel ssc=ServerSocketChannel.open();
		ssc.bind(new InetSocketAddress(12345));
		ssc.configureBlocking(false);//设为非阻塞		
		ArrayList<SocketChannel> chans=new ArrayList<>();
		
		while(true) {
			SocketChannel sc=ssc.accept();
			if(sc!=null){
				//非阻塞,无连接返回空
				System.out.println("connected"+sc.toString());
				sc.configureBlocking(false);//客户端套接字非阻塞，无数据读出0			
				chans.add(sc);
			}
			for (SocketChannel sc1 : chans ) {
				if(sc1.read(buffer)<=0) continue;
				buffer.flip();
				byte[] b=new byte[buffer.remaining()];
				buffer.get(b);
				buffer.clear();
				System.out.printf("%s:\n%s\n",sc1.getRemoteAddress().toString(),new String(b,"UTF-8"));				
			}			
		}
	}
```

##### selector监听接受和读

```java
public static void main(String[] args) throws IOException{
		ServerSocketChannel ssc=ServerSocketChannel.open().bind(new InetSocketAddress(12345));
		System.out.println("Listening...");
		ssc.configureBlocking(false);
		Selector selector=Selector.open();
		SelectionKey key =  ssc.register(selector, 0,null);//注册
		key.interestOps(SelectionKey.OP_ACCEPT);
		ByteBuffer buf=ByteBuffer.allocate(512);
		
		while(true) {
			selector.select();//监听所有套接字
			Iterator<SelectionKey> itr=selector.selectedKeys().iterator();
			//遍历选中集
			while(itr.hasNext()) {
				SelectionKey k=itr.next();
				itr.remove();//选中集读出key必移除			
				if(k.isAcceptable()) {
					//处理连接事件
					ServerSocketChannel ssc1 = (ServerSocketChannel)key.channel();
					SocketChannel sc=ssc1.accept();
					sc.configureBlocking(false).register(selector, 0,null).interestOps(SelectionKey.OP_READ);//非阻塞，注册进selector，读感兴趣
					System.out.println(sc.getRemoteAddress().toString()+" connected");
				}else if(k.isReadable()) {
					//处理读事件
					try {
						SocketChannel sc=(SocketChannel)k.channel();
						if(sc.read(buf)==-1) {
							k.cancel();//客户端套接字正常关闭,从注册集中删除
						}else {
							buf.flip();//切换
							System.out.printf("%s : %s\n",sc.getRemoteAddress().toString(),Charset.forName("GBK").decode(buf));//正常输出消息
							buf.compact();
						}		
					} catch (IOException e) {
						System.out.println(e.toString());
						k.cancel();//异常关闭
					}			
				}
			}
		}
	}
```



##### 附件

```
key.attach(附件)
key.attachment()->附件
```

##### 判断可写

```java
public static void main(String args[]) throws IOException{
		ServerSocketChannel ssc=(ServerSocketChannel)ServerSocketChannel.open().bind(new InetSocketAddress(12345)).configureBlocking(false);
		Selector selector =Selector.open();
		ssc.register(selector, SelectionKey.OP_ACCEPT);
		
		while(true) {
			selector.select();
			Iterator<SelectionKey> itr=selector.selectedKeys().iterator();
			while(itr.hasNext()) {
				SelectionKey key = itr.next();
				itr.remove();			
				if(key.isAcceptable()) {
					((ServerSocketChannel)key.channel()).accept().configureBlocking(false).register(selector, SelectionKey.OP_WRITE);
					//.....向删除发送大量数据
				}else if(key.isWritable()) {
					if(key.attachment()==null) key.attach(ByteBuffer.allocate(32));
					ByteBuffer buf=(ByteBuffer)key.attachment();

					SocketChannel sc=(SocketChannel)key.channel();
					sc.write(buf);
					if(!buf.hasRemaining()) {
						key.interestOps(key.interestOps()-SelectionKey.OP_WRITE);//取消检测可写
						key.attach(null);//删除写缓存
					}				
				}
			}
		}		
	}
```

