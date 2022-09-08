# **1、**并发模型

```
为Reactor+非阻塞IO+线程池，新连接Round Robin分配；
```

# **2、TIPs**

## **1、非阻塞io**

知识点：

```
//设置非阻塞 fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0) | O_NONBLOCK);
```

## **2、function bind函数**

```
通过function类型可以将多个不同类型的对象，整合到一个类型中。
```

## **3、chrono**

```c++
#include <chrono>
#include <iostream>
int main()
{
    // 以下为5分钟表达
    std::chrono::minutes minute1{5}; // 5个1分钟
    std::chrono::duration<int, std::ratio<5*60, 1>> minute2{1}; // 1个5分钟
    std::chrono::duration<double, std::ratio<2*60, 1>> minute3{2.5}; // 2.5个2分钟

    std::cout <<  "minutes1 duration has " << minute1.count() << " ticks\n"
              <<  "minutes2 duration has " << minute2.count() << " ticks\n"
              <<  "minutes3 duration has " << minute3.count() << " ticks\n";

    // 一下为12小时表达
    std::chrono::hours hours1{12}; // 12个1小时
    std::chrono::duration<double, std::ratio<60*60*24, 1>> hours2{0.5}; // 0.5个1天

    std::cout <<  "hours1 duration has " << hours1.count() << " ticks\n"
              <<  "hours2 duration has " << hours2.count() << " ticks\n";

    // 使用 std::chrono::duration_cast<T> 将分钟间隔转化成标准秒间隔
    std::cout <<  "minutes1 duration has " <<
        std::chrono::duration_cast<std::chrono::seconds>(minute1).count() << " seconds\n";
}
```



## **4、regex正则表达式**

1. \ 表示将下一字符标记为特殊字符、转义字符；
2. C++中要注意转义字符，比如：“\d+”；
3.  ^ 表示字符串的开始，匹配输入字符串开始的位置； 
4. $ 表示字符串的结尾，匹配输入字符串结尾的位置；
5.  . 表示匹配除换行符" \n "以外的任意字符；
6.  \w 表示任意字母、数字、下划线 ；
7.  \s 表示任意空白符(tab也包含在内)；
8.  \d 表示匹配单个数字字符，\D 表示非数字字符匹配；
9.  [] 表示一个字符集合，匹配指定范围内的任何字符，例如[a-z]表示字母a~z所组成的集合；
10.  []中使用^来表示集合的补集，匹配不在指定的范围内的任何字符，例如1-3表示除1 2 3以外数字；
11.  [[:alpha:]] 表示任何字母； [[:alnum:]] 表示任何字母和数字；
12.  regex::icase 表示匹配时忽略大小写；
13.  {n} 表示正好匹配 n 次前面的字符或表达式，例如"hello{6}",匹配字符串中符合第二个l后边有6个o的子字符串； {n, } 表示至少匹配 n 次前面的字符或表达式；
14.  {n,m} 表示匹配至少 n 次，至多 m 次前面的字符或表达式；
15.  ? 表示零次或一次匹配前面的字符或子表达式； 
16. \t \n \r这些平时非常常见，分别表示制表符匹配、换行符匹配、回车符匹配

## **5、search函数**

```c++
//str1.begin str1.end  str2.begin  str2.end   匹配到返回str2.begin  
const char* lineEnd = search(buff.Peek(), buff.BeginWriteConst(), CRLF, CRLF + 2);
```



## **6、readv writev**

但是多次系统调用+拷贝会带来较大的开销，所以UNIX提供了另外两个函数—readv()和writev()，它们只需一次系统调用就可以实现在文件和进程的多个缓冲区之间传送数据，免除了多次系统调用或复制数据的开销。 read和write的衍生函数，readv和writev可以在一个原子操作中读取或写入多个缓冲区。

## **7、**Linux 内核 内存管理 文件映射

# **3、综述**

## **1、WebServer**

用C++实现的高性能WEB服务器，经过webbenchh压力测试可以实现上万的QPS

## **2、功能**

```
利用IO复用技术Epoll与线程池实现多线程的Reactor高并发模型； 利用正则与状态机解析HTTP请求报文，实现处理静态资源的请求； 利用标准库容器封装char，实现自动增长的缓冲区;
基于小根堆实现的定时器，关闭超时的非活动连接； 
利用单例模式与阻塞队列实现异步的日志系统，记录服务器运行状态；
利用RAII机制实现了数据库连接池，减少数据库连接建立与关闭的开销，同时实现了用户注册登录功能。 
增加logsys,threadpool测试单元(todo: timer, sqlconnpool, httprequest, httpresponse) 
实现config配置
```

## **3、注释**

Webserver的核心d代码注释，从整体上解释，

代码中利用了各种c++的特性和系统函数，实现起来方便，高效

细节注释见源码

目录树 

```
├── code           源代码 
│	├── buffer
│  	├── config
│  	├── http
│	├── log
│	├── timer
│  	├── pool
│  	├── server
│  	└── main.cpp
```

梳理：根据目录树 从整体来 了解代码

### **1、buffer**

```
对一个文件描述符进行读写操作，需要可自动调整大小的缓冲区 操作： 维护读写两个指针记录当前读写位置，读过取走的数据清空 扩容：若写指针达到当前buff尾，且数据未读完 缩减：每次操作完成，重置缓冲区 
```

### **2、config**

```
用于实现从配置文件的实现动态配置，加载配置文件解析键值对，动态参数配置，避免了对源码的修改
```

### **3、http**

实现http层的逻辑代码

### **4、log**

日志系统 用于调试代码 查看系统信息

### **5、timer**

小根堆实现的定时器 

- 添加时间复杂度为O(1); 
- 删除时间复杂度为O(1); 
- 执行一个定时器的时间复杂度为O(1); 
- 比起传统的按照固定时间间隔执行tick函数的链表/时间轮定时器，小根堆定时器可以动态地将所有定时器时间的最小的一个定时器的超时值作为心博时间。 这样，一旦心博函数tick()被调用，则超时时间最小的定时器一定到期，执行相关处理。然后将下一个最小值定时器作为下一次的超时时间。这样，减少了调用tick()的次数。 由此可见，最小堆定时器相比链表定时器和时间轮定时器的效率会更好些。 

### **6、pool**

资源池 /实现线程池，连接池； 利用单例模式，实现资源复用， 避免频繁资源的创建销毁带来的性能损耗/

### **7、server**

服务器代码的实现 

### **8、main**

主函数入门

# **4、实现**

见作者：https://github.com/markparticle/WebServer

# **5、致谢**

学而不思则罔、思而不学则怠

感谢作者[**markparticle** MARK](https://github.com/markparticle)，通过该项目学到了很多，入门第一课

链接

[并发模型](https://github.com/linyacool/WebServer/blob/master/并发模型.md)|

[连接的维护](https://github.com/linyacool/WebServer/blob/master/连接的维护.md)|

[版本历史](https://github.com/linyacool/WebServer/blob/master/版本历史.md) | 

[测试及改进](https://github.com/linyacool/WebServer/blob/master/测试及改进.md) | 

[项目目的](https://github.com/linyacool/WebServer/blob/master/项目目的.md) | 

[面试问题](https://github.com/linyacool/WebServer/blob/master/面试问题.md)