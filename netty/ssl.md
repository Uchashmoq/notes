## HTTPS服务器

```java
public class HttpsServer {
    public static void main(String[] args) throws Exception {
        // 创建自签名证书
        SelfSignedCertificate cert = new SelfSignedCertificate();
        SslContext sslCtx = SslContextBuilder.forServer(cert.certificate(), cert.privateKey()).build();

        EventLoopGroup bossGroup = new NioEventLoopGroup();
        EventLoopGroup workerGroup = new NioEventLoopGroup();
        
        try {
            ServerBootstrap serverBootstrap = new ServerBootstrap();
            serverBootstrap.group(bossGroup, workerGroup)
                .channel(NioServerSocketChannel.class)
                .childHandler(new ChannelInitializer<Channel>() {
                    @Override
                    protected void initChannel(Channel ch) throws Exception {
                        ch.pipeline().addLast(sslCtx.newHandler(ch.alloc()));
                        ch.pipeline().addLast(new HttpServerCodec());
                        ch.pipeline().addLast(new YourHttpHandler()); // 自定义的 HTTP 请求处理器
                    }
                })
                .option(ChannelOption.SO_BACKLOG, 128)
                .childOption(ChannelOption.SO_KEEPALIVE, true);

            // 绑定端口并启动服务器
            Channel ch = serverBootstrap.bind(8443).sync().channel();
            ch.closeFuture().sync();
        } finally {
            bossGroup.shutdownGracefully();
            workerGroup.shutdownGracefully();
        }
    }
}
```

### 证书

自签名

```java
//自签名证书
SelfSignedCertificate cert = new SelfSignedCertificate();
SslContext sslCtx = SslContextBuilder.forServer(cert.certificate(), cert.privateKey()).build();
```

```java
//pem文件
// 证书文件和私钥文件的路径

openssl req -newkey rsa:2048 -nodes -keyout private-key.pem -x509 -days 365 -out certificate.pem

String certificateFilePath = "your-certificate.pem"; // 替换成你的证书文件路径
String privateKeyFilePath = "your-private-key.pem";   // 替换成你的私钥文件路径
// 创建 SSL/TLS 上下文
SslContext sslCtx = SslContextBuilder
     .forServer(new File(certificateFilePath), new File(privateKeyFilePath))
     .build();
```

