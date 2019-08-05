#ifndef EXECUTETHREAD_H
#define EXECUTETHREAD_H

#include <QThread>

class ExecuteThread final : public QThread
{
    Q_OBJECT
private:
    static ExecuteThread *_S_assist_thread;//辅助线程
    static ExecuteThread *_S_parser_thread;//解析线程

    ExecuteThread()
    { start(); }
public:
    static ExecuteThread* assist_thread() { return _S_assist_thread; }
    static ExecuteThread* parser_thread() { return _S_parser_thread; }

    virtual void run() override { exec(); }
};

#endif // EXECUTETHREAD_H
