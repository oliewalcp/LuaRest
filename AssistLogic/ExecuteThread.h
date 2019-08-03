#ifndef EXECUTETHREAD_H
#define EXECUTETHREAD_H

#include <QThread>

class ExecuteThread final : public QThread
{
    Q_OBJECT
public:
    virtual void run() override { exec(); }
};

#endif // EXECUTETHREAD_H
