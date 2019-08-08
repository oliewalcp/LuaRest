#ifndef THREADMUTEX_H
#define THREADMUTEX_H

#include <condition_variable>
#include <mutex>
#include <atomic>

class ThreadMutex
{
private:
//    std::condition_variable _M_cv;
//    std::mutex _M_mutex;
    std::atomic<bool> _M_writing;

    static ThreadMutex *_S_thread_mutex;

    ThreadMutex() { }
public:
    static ThreadMutex* instance()
    { return _S_thread_mutex; }

    typedef std::unique_lock<std::mutex> UniqueLock;

    [[nodiscard]] UniqueLock* lock(const bool write = true);
    void unlock(UniqueLock *unique_lock);
};

#endif // THREADMUTEX_H
