#ifndef CODESPACE_H
#define CODESPACE_H

#include <QWidget>

namespace Ui {
class CodeSpace;
}

class CodeSpace : public QWidget
{
    Q_OBJECT

public:
    explicit CodeSpace(QWidget *parent = nullptr);
    ~CodeSpace();

private:
    Ui::CodeSpace *ui;
};

#endif // CODESPACE_H
