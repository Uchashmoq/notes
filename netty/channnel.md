### ByteBuffer

```java
import java.io.File;
import java.io.FileInputStream;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;

public class Main {
	public static void main(String[] args) throws Exception{
		FileInputStream fis=new FileInputStream(new File("C:\\eclp\\nioDemo\\src\\byteBuffer\\test.txt"));
		FileChannel fchan=fis.getChannel();
		ByteBuffer buf=ByteBuffer.allocate(10);
		//buf.put(b0,b1,b2...);写字节
		while(fchan.read(buf)!=-1) {
			buf.flip();//读模式
			while(buf.hasRemaining()) {//buf是否有剩余
				System.out.printf("%c ",(char)buf.get());
                //int n=fchan.write(buf)从buf读到fchan
			}
			System.out.println("");
			buf.clear();//写模式,或compact
		}
	}
}

```

更多方法

```java
buf.rewind() //归零
buf.get(byte组)//读多个
    .mark()
    .reset()//从mark的位置开始
    .get(i)//从索引开始 
    
public abstract long transferTo(long position, long count, WritableByteChannel target) throws IOException;
//通道转换 

```

字符串转buffer

```java
//1.
ByteBuffer buf=ByteBuffer.allocate(16);
buf.put("nihao".getBytes(Charset.forName("UTF-8")));
//2.
ByteBuffer buf1=StandardCharsets.UTF_8.encode("你好");
//3.
ByteBuffer buf2=ByteBuffer.wrap("你好".getBytes());
```

  集中写

```java
ByteBuffer buf=ByteBuffer.allocate(16);
		buf.put("nihao".getBytes(Charset.forName("UTF-8")));
		ByteBuffer buf1=StandardCharsets.UTF_8.encode("你好");
		ByteBuffer buf2=ByteBuffer.wrap("你好".getBytes());
		
		try(FileChannel fchan=new RandomAccessFile("C:\\eclp\\nioDemo\\src\\byteBuffer\\test.txt", "rw").getChannel()) {
			fchan.write(new ByteBuffer[]{buf,buf1,buf2});
		} catch (Exception e) {
			e.printStackTrace();
		}
```

集中读

```
fchan.read(new ByteBuffer[]{buf0,buf1,buf2});
```

通道转换

```
a.transferTo(位置,大小,to);
```

遍历文件夹

```java
 Path rootDir = Path.of("/path/to/directory"); // 指定要遍历的文件夹路径

        Files.walkFileTree(rootDir, new SimpleFileVisitor<>() {
            @Override
            public FileVisitResult visitFile(Path file, BasicFileAttributes attrs) throws IOException {
                // 处理文件
                System.out.println("File: " + file);
                return FileVisitResult.CONTINUE;
            }

            @Override
            public FileVisitResult preVisitDirectory(Path dir, BasicFileAttributes attrs) throws IOException {
                // 在进入子文件夹之前处理文件夹
                System.out.println("Directory: " + dir);
                return FileVisitResult.CONTINUE;
            }

            @Override
            public FileVisitResult postVisitDirectory(Path dir, IOException exc) throws IOException {
                // 在处理完子文件夹后处理文件夹
                return FileVisitResult.CONTINUE;
            }

            @Override
            public FileVisitResult visitFileFailed(Path file, IOException exc) throws IOException {
                // 处理文件访问失败的情况
                System.err.println("Failed to visit file: " + file);
                return FileVisitResult.CONTINUE;
            }
        });
```



