#include "CodeSpace.h"
#include "ui_CodeSpace.h"

CodeSpace::CodeSpace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CodeSpace)
{
    ui->setupUi(this);
}

CodeSpace::~CodeSpace()
{
    delete ui;
}
