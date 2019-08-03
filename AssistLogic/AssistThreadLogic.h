#ifndef ASSISTTHREADLOGIC_H
#define ASSISTTHREADLOGIC_H

#include "ExecuteThread.h"
#include <atomic>
#include <memory>
#include <QString>

struct TreeItemPosition
{
private:
    union {
        unsigned long long _M_total;
        struct {
            int _M_row;
            int _M_column;
        } _M_part;
    } _M_position;
public:
    TreeItemPosition() { }
    TreeItemPosition(int r, int c)
    {
        row() = r;
        column() = c;
    }
    TreeItemPosition(const TreeItemPosition &pos)
    { _M_position._M_total = pos._M_position._M_total; }
    TreeItemPosition(TreeItemPosition &&pos)
    { _M_position._M_total = std::forward<TreeItemPosition>(pos)._M_position._M_total; }
    TreeItemPosition(unsigned long long arg)
    { _M_position._M_total = arg; }
    int& row() { return _M_position._M_part._M_row; }
    int& column() { return _M_position._M_part._M_column; }
};

class AssistThreadLogic : public QObject
{
    Q_OBJECT
private:
    ExecuteThread *_M_thread;
    std::atomic<bool> _M_working;

    static AssistThreadLogic *_S_assist_logic;

    AssistThreadLogic();
public:
    static const AssistThreadLogic* instance() { return _S_assist_logic; }

private:
    void load_directory(const QString &dir);
public slots:
    void load_directory_tree_slot(std::shared_ptr<QString> ptr);
signals:
    void add_tree_node_signal(const QString *, unsigned long long, bool);

};

#endif // ASSISTTHREADLOGIC_H
