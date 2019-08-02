#ifndef PROJECTTREESPACE_H
#define PROJECTTREESPACE_H

#include <QWidget>
#include <memory>

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
    void on_OpenDirButton_clicked();

private:
    Ui::ProjectTreeSpace *ui;

    void load_directory(std::shared_ptr<QString> dir);
    void clear_tree();

signals:
    void select_directory_signal(std::shared_ptr<QString>);
};

#endif // PROJECTTREESPACE_H
