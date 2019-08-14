#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "AssistLogic/ThreadMutex.h"
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _M_CodeSpaceWidget = new CodeSpace(this);
    _M_ProjectTreeSpaceWidget = new ProjectTreeSpace(this);
    ui->CodeContentArea->addWidget(_M_CodeSpaceWidget);
    ui->ProjectTreeContent->addWidget(_M_ProjectTreeSpaceWidget);
    ui->ProgressBar->hide();
    ui->Text->hide();
    _M_notify_timer = new QTimer;
    connect(_M_notify_timer, SIGNAL(timeout()), this, SLOT(timeout_slot()));
    _M_notify_timer->setInterval(100);
    _M_notify_timer->start();
}

MainWindow::~MainWindow()
{
    delete _M_notify_timer;
    delete ui;
}

void MainWindow::timeout_slot()
{
    ThreadMutex::instance()->notify();
}
