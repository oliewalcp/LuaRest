#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CodeSpace.h"
#include "ProjectTreeSpace.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

private:
    Ui::MainWindow *ui;

    CodeSpace *_M_CodeSpaceWidget;
    ProjectTreeSpace *_M_ProjectTreeSpaceWidget;
};

#endif // MAINWINDOW_H
