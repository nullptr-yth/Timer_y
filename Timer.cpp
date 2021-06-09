//
// Created by yth on 21-5-25.
//

#include "Timer.h"

void ThreadFunc(Timer* p,PTaskFunc pTask, void* argv)
{
    p->ThreadFuncCallback(pTask,argv);
}

Timer::Timer()
{
    m_nTimerStatus = TIMER_SUCCESS;  //定时器状态
    m_uInterval = 0; //定时时间
    m_pthTimerThread = nullptr;  //运行定时器任务的线程
}

Timer::Timer(const Timer &t)
{
}

int Timer::Init(unsigned int uInterval, PTaskFunc pTask, void *argv)
{
    if(m_nTimerStatus == TIMER_START)
    {
        return TIMER_START;
    }
    if (m_pthTimerThread!= nullptr)
    {
        return TIMER_INITERR;
    }
    m_uInterval = uInterval;
    m_pthTimerThread = new thread(ThreadFunc,this,pTask,argv);
    return TIMER_SUCCESS;
}

unsigned int Timer::start()
{
    m_nTimerStatus = TIMER_START;
    m_condControl.notify_all();
    return TIMER_SUCCESS;
}

unsigned int Timer::stop()
{
    m_nTimerStatus = TIMER_STOP;
    return TIMER_SUCCESS;

}

unsigned int Timer::killer()
{
    m_nTimerStatus = TIMER_KILLER;
    if (m_pthTimerThread != nullptr)
    {
        m_pthTimerThread->join();
        delete m_pthTimerThread;
        m_pthTimerThread = nullptr;
    }
    return TIMER_SUCCESS;
}

void Timer::ThreadFuncCallback(PTaskFunc pTask, void *argv)
{
    while (m_nTimerStatus!=TIMER_KILLER)
    {
        if (m_nTimerStatus!=TIMER_START&&m_nTimerStatus!=TIMER_KILLER)
        {
            cout<<"Timer waiting for start"<<endl;
            std::unique_lock<mutex> locker(m_mutexStart);
            m_condControl.wait(locker);
            cout<<"Timer is starting"<<endl;
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(m_uInterval));
            pTask(argv);
        }
    }
}

Timer::~Timer()
{
    if (m_nTimerStatus!=TIMER_KILLER)
    {
        killer();
    }
}

unsigned int Timer::GetInterval()
{
    return m_uInterval;
}

