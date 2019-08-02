#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _M_CodeSpaceWidget = new CodeSpace(this);
    _M_ProjectTreeSpaceWidget = new ProjectTreeSpace(this);
    ui->CodeContentArea->addWidget(_M_CodeSpaceWidget);
    ui->CodeContentArea->addWidget(_M_ProjectTreeSpaceWidget);
    ui->ProgressBar->hide();
    ui->Text->hide();

    connect(_M_ProjectTreeSpaceWidget, SIGNAL(select_directory_signal(std::shared_ptr<QString>)),
            this, SLOT(select_directory_slot(std::shared_ptr<QString>)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::select_directory_slot(std::shared_ptr<QString> dir)
{
    // 联系解析器
    dir.reset();
}