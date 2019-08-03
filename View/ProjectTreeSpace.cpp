#include "ProjectTreeSpace.h"
#include "ui_ProjectTreeSpace.h"
#include "AssistLogic/AssistThreadLogic.h"
#include <QFileDialog>
#include <QFile>

ProjectTreeSpace::ProjectTreeSpace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectTreeSpace)
{
    ui->setupUi(this);
    _M_item_map = new TreeItemMap();
    _M_model = new QStandardItemModel();
    ui->ProjectTree->setModel(_M_model);
    ui->ProjectTree->hide();

    const AssistThreadLogic *logic = AssistThreadLogic::instance();
    connect(this, SIGNAL(load_directory_tree_signal(std::shared_ptr<QString>)),
            logic, SLOT(load_directory_tree_slot(std::shared_ptr<QString>)));
    connect(logic, SIGNAL(add_tree_node_signal(const QString *, unsigned long long, bool)),
            this, SLOT(add_tree_node_slot(const QString *, unsigned long long, bool)));
}

ProjectTreeSpace::~ProjectTreeSpace()
{
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
 * param[name]:结点名称， need delete
 * param[pos]:结点位置
 * param[is_dir]:是否文件夹
 */
void ProjectTreeSpace::add_tree_node_slot(const QString *name, unsigned long long pos, bool is_dir)
{
    TreeItemPosition position(pos);
    auto it = _M_item_map->find(pos);
    if(it != _M_item_map->end())
    {
        delete it->second;
        _M_item_map->erase(it);
    }
    QStandardItem *item = new QStandardItem(*name);
    if(is_dir)
    {
        item->setIcon(QIcon(":/Image/Icon/directory.jpg"));
    }
    else
    {
        item->setIcon(QIcon(":/Image/Icon/file.jpg"));
    }
    _M_model->setItem(position.row(), position.column(), item);
    _M_item_map->insert(std::pair(pos, item));
    delete name;
}

void ProjectTreeSpace::clear_tree()
{

}
