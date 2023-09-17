### 写

```java
writeByte(byte value)：写入一个字节。
writeShort(short value)：写入一个短整数。
writeInt(int value)：写入一个整数。
writeLong(long value)：写入一个长整数。
writeFloat(float value)：写入一个单精度浮点数。
writeDouble(double value)：写入一个双精度浮点数。
writeBytes(byte[] src)：写入字节数组。
writeBytes(ByteBuf src)：写入另一个ByteBuf的内容。
```

### 读

```java
readByte()：读取一个字节。
readShort()：读取一个短整数。
readInt()：读取一个整数。
readLong()：读取一个长整数。
readFloat()：读取一个单精度浮点数。
readDouble()：读取一个双精度浮点数。
readBytes(byte[] dst)：将字节数据读取到指定的字节数组中。
readBytes(ByteBuf dst)：将字节数据读取到另一个ByteBuf中。
```

### 其他

```java
capacity()：返回ByteBuf的容量。
readableBytes()：返回可读取的字节数。
writableBytes()：返回可写入的字节数。
readerIndex()：返回当前读取位置的索引。
writerIndex()：返回当前写入位置的索引。
markReaderIndex()和resetReaderIndex()：设置和重置读取位置的标记。
markWriterIndex()和resetWriterIndex()：设置和重置写入位置的标记。
clear()：清空ByteBuf的内容。
release()：释放ByteBuf占用的资源
retain():计数器加一
```

### Slice

```java
//不可扩容，原有buf release影响切片 
ByteBuf buffer = ByteBufAllocator.DEFAULT.buffer();
        for(byte i='a';i<='j';i++){
            buffer.writeByte(i);
        }
        show(buffer);

        ByteBuf slice = buffer.slice(0, 3);
        show(slice);
```

### 拷贝

```java
ByteBuf duplicate = buffer.duplicate();//零拷贝
ByteBuf copy = buffer.copy();//复制
```

### 合并

```java
CompositeByteBuf compositeByteBuf = ByteBufAllocator.DEFAULT.compositeBuffer(); 
compositeByteBuf.addComponents(true,duplicate,copy);
```

