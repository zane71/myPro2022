
#ifndef HEAP_TIMER_H
#define HEAP_TIMER_H

#include <queue>
#include <unordered_map>
#include <time.h>
#include <algorithm>
#include <arpa/inet.h> 
#include <functional> 
#include <assert.h> 
#include <chrono>
#include "../log/log.h"

typedef std::function<void()> TimeoutCallBack;

/*
using high_resolution_clock = steady_clock;
这是一个单调时钟，一旦启动之后就与系统时间没有关系了，完全根据物理是时间向前移动，
成员函数只有一个 now()，通常可以用来计时，使用方法与 system_clock 相比简单许多，
*/
typedef std::chrono::high_resolution_clock Clock;
//多少ms
typedef std::chrono::milliseconds MS;
//记录时间戳
// 先记录程序运行时间
//std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
typedef Clock::time_point TimeStamp;

struct TimerNode {
    int id;
    TimeStamp expires;//到期时间
    TimeoutCallBack cb;
    //重载<
    bool operator<(const TimerNode& t) {
        return expires < t.expires;
    }
};

/* 基于STL的小根堆定时器实现（C++）小根堆实现
1. 添加时间复杂度为O(1);
2. 删除时间复杂度为O(1);
3.执行一个定时器的时间复杂度为O(1);

4.比起传统的按照固定时间间隔执行tick函数的链表/时间轮定时器，小根堆定时器可以动态地将所有定时器时间的最小的一个定时器的超时值作为心博时间。这样，一旦心博函数tick()被调用，则超时时间最小的定时器一定到期，执行相关处理。然后将下一个最小值定时器作为下一次的超时时间。这样，减少了调用tick()的次数。
由此可见，最小堆定时器相比链表定时器和时间轮定时器的效率会更好些。
因为C++的内部已经有优先队列，直接调用相关函数就可以构建堆、增加、修改等操作，
*/
class HeapTimer {
public:
    HeapTimer() { heap_.reserve(64); }

    ~HeapTimer() { clear(); }
    
    void adjust(int id, int newExpires);

    void add(int id, int timeOut, const TimeoutCallBack& cb);

    void doWork(int id);

    void clear();

    void tick();

    void pop();

    int GetNextTick();

private:
    void del_(size_t i);
    
    void siftup_(size_t i);

    bool siftdown_(size_t index, size_t n);

 // unsigned int
    void SwapNode_(size_t i, size_t j);

    std::vector<TimerNode> heap_;

    std::unordered_map<int, size_t> ref_;
};

#endif //HEAP_TIMER_H