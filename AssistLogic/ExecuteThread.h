#ifndef EXECUTETHREAD_H
#define EXECUTETHREAD_H

#include <QThread>

class ExecuteThread final : QThread
{
    Q_OBJECT
private:
    static ExecuteThread *_S_assist_thread;//辅助线程
    static ExecuteThread *_S_parser_thread;//解析线程

    ExecuteThread();
public:
    static QThread* assist_thread();
    static QThread* parser_thread();
protected:
    void run() Q_DECL_OVERRIDE { exec(); }
};

#endif // EXECUTETHREAD_H

