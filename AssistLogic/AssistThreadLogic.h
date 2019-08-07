#ifndef ASSISTTHREADLOGIC_H
#define ASSISTTHREADLOGIC_H

#include <memory>
#include <QString>
#include <QObject>

class AssistThreadLogic final : public QObject
{
    Q_OBJECT
private:
    volatile bool _M_working;

    static AssistThreadLogic *_S_assist_logic;

    AssistThreadLogic();
public:
    static const AssistThreadLogic* instance() { return _S_assist_logic; }

    bool is_working() { return _M_working; }

private:
    void load_directory(const QString &dir, int level = 0);
public slots:
    void load_directory_tree_slot(std::shared_ptr<QString> ptr);
signals:
    void add_tree_node_signal(QString *, unsigned int);

};

#endif // ASSISTTHREADLOGIC_H
