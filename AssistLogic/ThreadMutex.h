#ifndef THREADMUTEX_H
#define THREADMUTEX_H

#include <condition_variable>
#include <mutex>

class ThreadMutex
{
private:
    std::condition_variable _M_cv;
    std::mutex _M_mutex;

    typedef std::unique_lock<std::mutex> UniqueLock;

    static ThreadMutex *_S_thread_mutex;

    ThreadMutex() { }
public:
    static ThreadMutex* instance()
    { return _S_thread_mutex; }

    UniqueLock* lock()
    {
        UniqueLock *unique_lock = new UniqueLock(_M_mutex);
        _M_cv.wait(*unique_lock);
        return unique_lock;
    }
    void unlock(UniqueLock *unique_lock)
    {
        unique_lock->unlock();
        _M_cv.notify_all();
    }
};

#endif // THREADMUTEX_H
