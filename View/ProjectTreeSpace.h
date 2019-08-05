#ifndef PROJECTTREESPACE_H
#define PROJECTTREESPACE_H

#include <QWidget>
#include <memory>
#include <QTreeWidgetItem>

namespace Ui {
class ProjectTreeSpace;
}

class ProjectTreeSpace : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectTreeSpace(QWidget *parent = nullptr);
    ~ProjectTreeSpace();

private slots:
    void on_OpenDirButton_clicked(); // 选择文件夹按钮点击事件
    void add_tree_node_slot(QString *name, unsigned int flag);

private:
    Ui::ProjectTreeSpace *ui;

    void clear_tree();

signals:
    void load_directory_tree_signal(std::shared_ptr<QString>);
};

#endif // PROJECTTREESPACE_H
