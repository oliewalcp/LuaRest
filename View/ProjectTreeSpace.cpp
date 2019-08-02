#include "ProjectTreeSpace.h"
#include "ui_ProjectTreeSpace.h"
#include <QFileDialog>
#include <QFile>

ProjectTreeSpace::ProjectTreeSpace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectTreeSpace)
{
    ui->setupUi(this);
    ui->ProjectTree->hide();
}

ProjectTreeSpace::~ProjectTreeSpace()
{
    delete ui;
}

void ProjectTreeSpace::on_OpenDirButton_clicked()
{
    std::shared_ptr<QString> select = std::make_shared<QString>(QFileDialog::getExistingDirectory(this));
    if(*select == "") return;
    emit select_directory_signal(select);
    ui->OpenDirButton->hide();
    ui->ProjectTree->show();
    clear_tree();
    load_directory(select);
    select.reset();
}

void ProjectTreeSpace::load_directory(std::shared_ptr<QString> dir)
{
    QDir directory(*dir);
    QStringList lua_files;
    lua_files.append(tr("*.[lL]{1}[Uu]{1}[aA]{1}"));
    QFileInfoList file_list = directory.entryInfoList(lua_files, QDir::Files);
    QFileInfoList dir_list = directory.entryInfoList();
    for(auto it = dir_list.begin(); it != dir_list.end(); ++it)
    {
        QFileInfo &file_info = *it;
        QString &&name = file_info.fileName();
        if(name == "." || name == "..") continue;
    }
}

void ProjectTreeSpace::clear_tree()
{

}
