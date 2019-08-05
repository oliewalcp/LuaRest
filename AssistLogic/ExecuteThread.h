#ifndef EXECUTETHREAD_H
#define EXECUTETHREAD_H

#include <QThread>

class ExecuteThread final : public QThread
{
    Q_OBJECT
private:
    static ExecuteThread *_S_assist_thread;

    ExecuteThread()
    { start(); }
public:
    static ExecuteThread* assist_thread() { return _S_assist_thread; }

    virtual void run() override { exec(); }
};

#endif // EXECUTETHREAD_H
