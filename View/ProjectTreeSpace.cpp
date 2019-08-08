#include "ProjectTreeSpace.h"
#include "ui_ProjectTreeSpace.h"
#include "AssistLogic/AssistThreadLogic.h"
#include "Data/ProjectTreeData.h"
#include <QFileDialog>
#include <QFile>
#include <QDebug>

ProjectTreeSpace::ProjectTreeSpace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectTreeSpace)
{
    ui->setupUi(this);
    ui->ProjectTree->hide();

    qRegisterMetaType<std::shared_ptr<QString>>("std::shared_ptr<QString>");
    const AssistThreadLogic *logic = AssistThreadLogic::instance();
    connect(this, SIGNAL(load_directory_tree_signal(std::shared_ptr<QString>)),
            logic, SLOT(load_directory_tree_slot(std::shared_ptr<QString>)));
    connect(logic, SIGNAL(add_tree_node_signal(QString *, unsigned int)),
            this, SLOT(add_tree_node_slot(QString *, unsigned int)));
}

ProjectTreeSpace::~ProjectTreeSpace()
{
    clear_tree();
    delete ui;
}

void ProjectTreeSpace::on_OpenDirButton_clicked()
{
    std::shared_ptr<QString> select = std::make_shared<QString>(QFileDialog::getExistingDirectory(this));
    if(*select == "") return;
    clear_tree();
    emit load_directory_tree_signal(select);
    ui->OpenDirButton->hide();
    ui->ProjectTree->show();
    select.reset();
}
/* 添加工程树结点
 * param[name]:结点名称
 * param[pos]:结点位置
 * param[is_dir]:是否文件夹
 */
void ProjectTreeSpace::add_tree_node_slot(QString *name, unsigned int flag)
{
    qDebug() << tr("new node name: ") << *name;
    QTreeWidgetItem *item = ProjectTreeData::instance()->item(*name, flag);
    qDebug() << tr("get item success");
    QTreeWidgetItem *parent = ProjectTreeData::instance()->parent(item);
    qDebug() << tr("get parent success");
    // 如果没有父结点，证明是根结点
    if(parent == nullptr)
    {
        ui->ProjectTree->addTopLevelItem(item);
        qDebug() << tr("total child size: ") << ui->ProjectTree->children().size();
    }
    delete name;
}

void ProjectTreeSpace::clear_tree()
{
    ui->ProjectTree->clear();
    ProjectTreeData::instance()->clear();
}
