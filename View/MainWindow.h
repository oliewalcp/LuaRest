#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
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

private:
    Ui::MainWindow *ui;

    QTimer *_M_notify_timer;
    CodeSpace *_M_CodeSpaceWidget;
    ProjectTreeSpace *_M_ProjectTreeSpaceWidget;
};

#endif // MAINWINDOW_H
