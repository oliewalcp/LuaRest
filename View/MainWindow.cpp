#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _M_CodeSpaceWidget = new CodeSpace(this);
    ui->CodeContentArea->addWidget(_M_CodeSpaceWidget);
    _M_ProjectTreeSpaceWidget = new ProjectTreeSpace(this);
    ui->CodeContentArea->addWidget(_M_ProjectTreeSpaceWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    QRect cs_rect = _M_CodeSpaceWidget->geometry();
    _M_CodeSpaceWidget->setGeometry(cs_rect.x(), cs_rect.y(), width() - _M_ProjectTreeSpaceWidget->width(), height() - _M_ProjectTreeSpaceWidget->height());
}
