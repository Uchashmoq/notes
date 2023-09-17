# Linux笔记2

##### 一、快捷键

Ctrl+c取消命令  Ctrl+d登出或退出程序  

!(命令开头) 执行最后一次匹配内容的命令  

Ctrl+r搜索历史命令，回车执行，左键输入

Ctrl+a跳到命令开头  Ctrl+e跳到结尾

Ctrl+左左跳一个单词

##### 二、安装软件

sudo apt【install或remove或upgrade】【软件名】

##### 三、服务管理

systemctl 【start，stop，status，enable，disable】【服务名】

NetworkManager 主网络服务

network 副网络服务

firewalld 防火墙服务

sshd，ssh服务 

##### 四、软链接

ln -s 【原路径】【新路径】

​	eg. ln -s ./1/2/3/4/test.txt ./test.txt

​	      ln -s ./1/2/3/4 ./444

##### 五、时间

1、date [+格式化占位符]

<img src="C:\Users\13637\Pictures\Screenshots\屏幕截图_20221118_195351.png" alt="屏幕截图_20221118_195351" style="zoom:25%;" />

2、date -d "+1 day" [+格式化占位符]

year month day hour minute second 

3、改时区

sudo rm -f /etc/localtime

sudo ln -s /usr/share/zoneinfo/Asia/Shanghai /etc/localtime

4、手动校准时间

sudo ntpdate -u ntp.aliyun.com

#### 六、SSH免密

vim /etc/hosts 配置IP和主机名映射

ssh-keygen -t rsa -b 4096 生成秘钥

ssh-copy-id 主机名

ssh '主机名' 登录





