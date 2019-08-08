#ifndef EXECUTETHREAD_H
#define EXECUTETHREAD_H

#include <QThread>

class ExecuteThread final : QThread
{
    Q_OBJECT
private:
    static ExecuteThread *_S_assist_thread;//辅助线程
    static ExecuteThread *_S_parser_thread;//解析线程

    ExecuteThread()
    { start(); }
public:
    static QThread* assist_thread()
    {
        if(_S_assist_thread == nullptr)
            _S_assist_thread = new ExecuteThread();
        return _S_assist_thread;
    }
    static QThread* parser_thread()
    {
        if(_S_parser_thread == nullptr)
            _S_parser_thread = new ExecuteThread();
        return _S_parser_thread;
    }
protected:
    void run() { exec(); }
};

#endif // EXECUTETHREAD_H
