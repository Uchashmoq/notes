## 寻址

8086地址总线20位，有1M的地址空间。寄存器16位，物理地址=段地址*16+偏移

段地址16位0~FFFFH ,偏移地址最多寻址64k

### 表示：

段:偏移  2000:1F60  (21F60)

## debug

1. 查看寄存器 r ax
2. d列出128字节 ; d 2000:1111 列出指定位置 ; d 2000:0 f 列出指定范围
3. e 2000:1111 12 34 56 78 修改内存数据
4. u 2000:0 f 查看代码
5. a 073f:100 mov ax,1234 向指定地址写入数据
6. t 执行 cs:ip处指令
7. rip，rcs修改ip，cs寄存器的值，代码将从 ip:cs处执行

## JMP

jmp 段:偏移 修改cs:ip值

jmp ax 修改ip

```assembly
mov ax,1
mov bx,106
add ax,2
jmp bx
```

## 段寄存器ds

```assembly
mov bx,222
mov ds,bx
mov [1],ax
mov cx,[1]
```

## 栈

ss:sp 栈顶指针

push ax

pop bx

### 编译链接

masm test.asm

link test.obj



