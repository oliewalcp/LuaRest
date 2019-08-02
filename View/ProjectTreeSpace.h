#ifndef PROJECTTREESPACE_H
#define PROJECTTREESPACE_H

#include <QWidget>

namespace Ui {
class ProjectTreeSpace;
}

class ProjectTreeSpace : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectTreeSpace(QWidget *parent = nullptr);
    ~ProjectTreeSpace();

private:
    Ui::ProjectTreeSpace *ui;
};

#endif // PROJECTTREESPACE_H
