#include "ProjectTreeData.h"
#include "AssistLogic/ThreadMutex.h"
#include <QDebug>

ProjectTreeData *ProjectTreeData::_S_project_tree_data = new ProjectTreeData();

ProjectTreeData::~ProjectTreeData()
{
    clear();
    delete _M_tree_node;
    delete _M_item_data;
}

/* 获取控件
 * param[name]:结点名称
 * param[level]:层数
 * param[is_dir]:是否文件夹
 */
QTreeWidgetItem* ProjectTreeData::item(QString &name, int level, bool is_dir)
{
    return item(new ItemDataType(&name, level, is_dir));
}

/* 获取控件
 * param[name]:结点名称
 * param[flag]:结点参数
 */
QTreeWidgetItem *ProjectTreeData::item(QString &name, unsigned int flag)
{
    return item(new ItemDataType(&name, flag));
}
/* 获取控件
 * param[data]:结点数据 need delete, reset
 */
QTreeWidgetItem *ProjectTreeData::item(ItemDataType *data)
{
    auto lock = ThreadMutex::instance()->lock(READ);
    QTreeWidgetItem *result = nullptr;
    auto it = _M_tree_node->find(data);
    if(it != _M_tree_node->end())
    {
        result = it->second;
    }
    ThreadMutex::instance()->unlock(lock);
    data->reset();
    delete data;
    return result;
}

QTreeWidgetItem *ProjectTreeData::parent(QTreeWidgetItem *child)
{
    QTreeWidgetItem *result = nullptr;
    auto lock = ThreadMutex::instance()->lock(READ);
    auto it = _M_item_data->find(child);
    if(it != _M_item_data->end())
    {
        auto data = it->second;
        result = data->parent();
    }
    ThreadMutex::instance()->unlock(lock);
    return result;
}

void ProjectTreeData::set_parent(QString &name, int level, bool is_dir, QTreeWidgetItem *parent)
{
    ItemDataType *data = new ItemDataType(&name, level, is_dir);
    auto it = _M_tree_node->find(data);
    if(it != _M_tree_node->end())
    {
        it->first->set_parent(parent);
        parent->addChild(it->second);
    }
    data->reset();
    delete data;
}
/* 设置树结点
 * param[name]:结点名称 need delete
 * param[level]:层次  结点所在层数（从0开始）
 * param[is_dir]:是否文件夹
 * param[item]:控件
 * param[parent]:父控件
 */
void ProjectTreeData::set_item(QString *name, int level, bool is_dir, QTreeWidgetItem *item, QTreeWidgetItem *parent)
{
    ItemDataType *data = new ItemDataType(name, level, is_dir, parent);
    qDebug() << __FILE__ << ":" << __func__ << ":" << __LINE__ << "\n" << *name;
    auto lock = ThreadMutex::instance()->lock(WRITE);
    auto it = _M_tree_node->find(data);
    // 如果已存在结点
    if(it != _M_tree_node->end())
    {
        delete data;
        if(it->second != nullptr)
        {
            delete it->second;
        }
        it->first->set_parent(parent);
        data = it->first;
        it->second = item;
    }
    else
    {
        _M_tree_node->insert(std::pair(data, item));
    }
    // 如果有新的结点控件，则插入到容器
    if(item != nullptr)
    {
        _M_item_data->insert(std::pair(item, data));
        if(parent != nullptr)
        {
            parent->addChild(item);
        }
    }
    ThreadMutex::instance()->unlock(lock);
    qDebug() << __FILE__ << ":" << __func__ << ":" << __LINE__ << "\n" << "current size: " << _M_tree_node->size();
}

void ProjectTreeData::add_item(QString *name, int level, bool is_dir, QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, *name);
    if(is_dir)
    {
        item->setIcon(0, QIcon(":/Image/Icon/directory.jpg"));
    }
    else
    {
        item->setIcon(0, QIcon(":/Image/Icon/file.jpg"));
    }
    set_item(name, level, is_dir, item, parent);
}

/* 删除控件
 * param[name]:结点名称
 * param[level]:层数
 * param[is_dir]:是否文件夹
 */
void ProjectTreeData::remove_element(QString &name, int level, bool is_dir)
{
    ItemDataType *data = new ItemDataType(&name, level, is_dir);
    auto lock = ThreadMutex::instance()->lock(WRITE);
    auto it = _M_tree_node->find(data);
    if(it->second != nullptr)
    {
        delete it->first;
        delete it->second;
    }
    data->reset();
    delete data;
    ThreadMutex::instance()->unlock(lock);
}
//释放空间
void ProjectTreeData::clear()
{
    for(auto it = _M_tree_node->begin(); it != _M_tree_node->end(); ++it)
    {
        delete it->first;
        if(it->second != nullptr)
            delete it->second;
    }
    _M_tree_node->clear();
    _M_item_data->clear();
}
