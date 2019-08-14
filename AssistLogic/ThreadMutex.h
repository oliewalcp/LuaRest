#ifndef THREADMUTEX_H
#define THREADMUTEX_H

#include <condition_variable>
#include <mutex>
#include <atomic>

enum Status : unsigned char {
    NONE,
    WRITE,
    READ
};

class ThreadMutex
{
private:
    std::condition_variable _M_cv;
    std::mutex _M_mutex;
    std::atomic<unsigned char> _M_status;

    static ThreadMutex *_S_thread_mutex;

    ThreadMutex()
    {
        _M_status = NONE;
    }
public:
    static ThreadMutex* instance()
    { return _S_thread_mutex; }

    typedef std::unique_lock<std::mutex> UniqueLock;

    [[nodiscard]] UniqueLock* lock(const Status status = NONE);
    void unlock(UniqueLock *unique_lock);

    void notify();
};

#endif // THREADMUTEX_H
