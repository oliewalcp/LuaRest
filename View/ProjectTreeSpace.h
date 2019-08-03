#ifndef PROJECTTREESPACE_H
#define PROJECTTREESPACE_H

#include <QWidget>
#include <memory>
#include <QStandardItem>

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
    void add_tree_node_slot(const QString *name, unsigned long long pos, bool is_dir);

private:
    typedef std::map<unsigned long long, QStandardItem*> TreeItemMap;

    Ui::ProjectTreeSpace *ui;
    QStandardItemModel *_M_model;
    TreeItemMap *_M_item_map;

    void clear_tree();

signals:
    void load_directory_tree_signal(std::shared_ptr<QString>);
};

#endif // PROJECTTREESPACE_H
