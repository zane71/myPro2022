
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
����һ������ʱ�ӣ�һ������֮�����ϵͳʱ��û�й�ϵ�ˣ���ȫ����������ʱ����ǰ�ƶ���
��Ա����ֻ��һ�� now()��ͨ������������ʱ��ʹ�÷����� system_clock ��ȼ���࣬
*/
typedef std::chrono::high_resolution_clock Clock;
//����ms
typedef std::chrono::milliseconds MS;
//��¼ʱ���
// �ȼ�¼��������ʱ��
//std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
typedef Clock::time_point TimeStamp;

struct TimerNode {
    int id;
    TimeStamp expires;//����ʱ��
    TimeoutCallBack cb;
    //����<
    bool operator<(const TimerNode& t) {
        return expires < t.expires;
    }
};

/* ����STL��С���Ѷ�ʱ��ʵ�֣�C++��С����ʵ��
1. ���ʱ�临�Ӷ�ΪO(1);
2. ɾ��ʱ�临�Ӷ�ΪO(1);
3.ִ��һ����ʱ����ʱ�临�Ӷ�ΪO(1);

4.����ͳ�İ��չ̶�ʱ����ִ��tick����������/ʱ���ֶ�ʱ����С���Ѷ�ʱ�����Զ�̬�ؽ����ж�ʱ��ʱ�����С��һ����ʱ���ĳ�ʱֵ��Ϊ�Ĳ�ʱ�䡣������һ���Ĳ�����tick()�����ã���ʱʱ����С�Ķ�ʱ��һ�����ڣ�ִ����ش���Ȼ����һ����Сֵ��ʱ����Ϊ��һ�εĳ�ʱʱ�䡣�����������˵���tick()�Ĵ�����
�ɴ˿ɼ�����С�Ѷ�ʱ���������ʱ����ʱ���ֶ�ʱ����Ч�ʻ����Щ��
��ΪC++���ڲ��Ѿ������ȶ��У�ֱ�ӵ�����غ����Ϳ��Թ����ѡ����ӡ��޸ĵȲ�����
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