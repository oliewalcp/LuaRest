#include "ProjectTreeSpace.h"
#include "ui_ProjectTreeSpace.h"

ProjectTreeSpace::ProjectTreeSpace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectTreeSpace)
{
    ui->setupUi(this);
}

ProjectTreeSpace::~ProjectTreeSpace()
{
    delete ui;
}
