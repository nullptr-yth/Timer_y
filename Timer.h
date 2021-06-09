//
// Created by yth on 21-5-25.
//

#ifndef TIMER_TIMER_H
#define TIMER_TIMER_H

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>  //条件变量
using namespace std;

enum
{
    TIMER_SUCCESS =0,
    TIMER_FAILED,
    TIMER_INITERR,
    TIMER_START,
    TIMER_STOP,
    TIMER_KILLER,
};


typedef void (*PTaskFunc)(void* argv);


class Timer
{
public:
    Timer();
    ~Timer();
    int Init(unsigned int uInterval,PTaskFunc pTask,void* argv);//interval:ms
    unsigned int start();
    unsigned int stop();
    unsigned int killer();
    void ThreadFuncCallback(PTaskFunc pTask, void* argv);
    unsigned int GetInterval();
private:
    Timer(const Timer&);  //为了防止使用拷贝构造
    Timer& operator= (const Timer&); //为了防止出现 赋值情况

private:
    std::atomic<int>        m_nTimerStatus;  //定时器状态
    unsigned int            m_uInterval; //定时时间
    std::thread*            m_pthTimerThread;  //运行定时器任务的线程
    std::condition_variable m_condControl; //控制线程用条件变量
    std::mutex              m_mutexStart;  //锁
};

void ThreadFunc(Timer* p,PTaskFunc pTask, void* argv);

#endif //TIMER_YTIMER_H
