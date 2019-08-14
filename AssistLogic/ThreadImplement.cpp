#include "ExecuteThread.h"
#include "ThreadMutex.h"
#include <chrono>

ExecuteThread *ExecuteThread::_S_assist_thread = nullptr;
ExecuteThread *ExecuteThread::_S_parser_thread = nullptr;
std::thread *ExecuteThread::_S_guard_thread = nullptr;
std::atomic<bool> ExecuteThread::_S_guard_thread_flag(true);//守护线程运行标志

ExecuteThread::ExecuteThread()
{
    start();
}

QThread *ExecuteThread::parser_thread()
{
    if(_S_parser_thread == nullptr)
        _S_parser_thread = new ExecuteThread();
    return _S_parser_thread;
}

void ExecuteThread::start_guard_thread()
{
    _S_guard_thread_flag = true;
    _S_guard_thread = new std::thread([](){
        while(_S_guard_thread_flag)
        {
            std::chrono::milliseconds time(100);
            std::this_thread::sleep_for(time);
            ThreadMutex::instance()->notify();
        }
        delete _S_guard_thread;
    });
    _S_guard_thread->detach();
}

void ExecuteThread::stop_guard_thread()
{
    _S_guard_thread_flag = false;
}

QThread *ExecuteThread::assist_thread()
{
    if(_S_assist_thread == nullptr)
        _S_assist_thread = new ExecuteThread();
    return _S_assist_thread;
}

ThreadMutex *ThreadMutex::_S_thread_mutex = new ThreadMutex();

ThreadMutex::UniqueLock *ThreadMutex::lock(const Status status)
{
    UniqueLock *unique_lock = new UniqueLock(_M_mutex);
    while((status == WRITE && _M_status == READ) || (status == READ && _M_status == WRITE))
        _M_cv.wait(*unique_lock);
    _M_status = status;
    return unique_lock;
}

void ThreadMutex::unlock(ThreadMutex::UniqueLock *unique_lock)
{
    unique_lock->unlock();
    _M_status = NONE;
    _M_cv.notify_all();
    delete unique_lock;
}

void ThreadMutex::notify()
{
    if(_M_status == NONE)
        _M_cv.notify_all();
}
