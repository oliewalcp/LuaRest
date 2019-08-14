#include "ExecuteThread.h"
#include "ThreadMutex.h"

ExecuteThread *ExecuteThread::_S_assist_thread = nullptr;
ExecuteThread *ExecuteThread::_S_parser_thread = nullptr;

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
    while(status == WRITE && _M_status == READ)
        _M_cv.wait(*unique_lock);
    while(status == READ && _M_status == WRITE)
        _M_cv.wait(*unique_lock);
    _M_status = status;
    return unique_lock;
}

void ThreadMutex::unlock(ThreadMutex::UniqueLock *unique_lock)
{
    unique_lock->unlock();
    _M_status = NONE;
    notify();
    delete unique_lock;
}

void ThreadMutex::notify()
{
    if(_M_status == NONE)
        _M_cv.notify_all();
}
