#ifndef EXECUTETHREAD_H
#define EXECUTETHREAD_H

#include <QThread>

class ExecuteThread final : QThread
{
    Q_OBJECT
private:
    static ExecuteThread *_S_assist_thread;//辅助线程
    static ExecuteThread *_S_parser_thread;//解析线程
    static std::thread *_S_guard_thread;//守护线程
    static std::atomic<bool> _S_guard_thread_flag;//守护线程运行标志

    ExecuteThread();
public:
    static QThread* assist_thread();
    static QThread* parser_thread();
    static void start_guard_thread();
    static void stop_guard_thread();
protected:
    void run() Q_DECL_OVERRIDE { exec(); }
};

#endif // EXECUTETHREAD_H

