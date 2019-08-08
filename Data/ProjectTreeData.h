#ifndef PROJECTTREEDATA_H
#define PROJECTTREEDATA_H

#include <QTreeWidgetItem>
#include <tuple>
#include <map>

struct ItemDataType
{
protected:
    union Uflag
    {
        struct Flag
        {
            int _M_is_dir : 1;
            int _M_level : 31;
        } Part;
        unsigned int Total;

        Uflag() : Total(0) { }
        Uflag(int level, bool is_dir)
        {
            Part._M_is_dir = is_dir;
            Part._M_level = level;
        }
        Uflag(unsigned int flag)
        { Total = flag; }
        Uflag(const Uflag &f)
        { Total = f.Total; }
    };
    typedef std::tuple<QString*, Uflag, QTreeWidgetItem*> DataType;
    DataType *_M_data;
public:
    ItemDataType(QString *name, int level, bool is_dir, QTreeWidgetItem *p = nullptr)
    {
        Uflag temp(level, is_dir);
        _M_data = new DataType(name, temp, p);
    }
    ItemDataType(QString *name, unsigned int flag, QTreeWidgetItem *p = nullptr)
    {
        Uflag temp(flag);
        _M_data = new DataType(name, temp, p);
    }
    ~ItemDataType()
    { reset(true); }
    // 释放空间
    // param[del]:是否删除字符串, true——delete
    void reset(bool del = false)
    {
        if(_M_data == nullptr) return;
        if(del) delete std::get<0>(*_M_data);
        delete std::get<2>(*_M_data);
        delete _M_data;
        _M_data = nullptr;
    }
    unsigned int flag()
    { return std::get<1>(*_M_data).Total; }
    QString& name()
    { return *std::get<0>(*_M_data); }
    bool is_dir()
    { return std::get<1>(*_M_data).Part._M_is_dir; }
    QTreeWidgetItem* parent()
    { return std::get<2>(*_M_data); }
    void set_parent(QTreeWidgetItem *p)
    { std::get<2>(*_M_data) = p; }
    int level()
    { return std::get<1>(*_M_data).Part._M_level; }
};

struct CompareStruct
{
    bool operator()(ItemDataType *tar, ItemDataType *src) const
    {
        bool temp = (tar->is_dir() == false) && (src->is_dir() == true);
        return tar->level() < src->level() || tar->name() < src->name() || temp;
    }
};

//写操作由辅助线程进行
class ProjectTreeData
{
private:
    static ProjectTreeData *_S_project_tree_data;
    typedef std::map<ItemDataType*, QTreeWidgetItem*, CompareStruct> TreeItemType;
    typedef std::map<QTreeWidgetItem*, ItemDataType*> TreeItemDataType;

    TreeItemType *_M_tree_node;//结点数据——结点
    TreeItemDataType *_M_item_data;//结点——结点数据

    ProjectTreeData() : _M_tree_node(new TreeItemType), _M_item_data(new TreeItemDataType) { }
public:
    ~ProjectTreeData();
    static ProjectTreeData* instance() { return _S_project_tree_data; }

    QTreeWidgetItem* item(QString &name, int level, bool is_dir);
    QTreeWidgetItem* item(QString &name, unsigned int flag);
    QTreeWidgetItem* item(ItemDataType *data);
    QTreeWidgetItem* parent(QTreeWidgetItem *child);
    void set_parent(QString &name, int level, bool is_dir, QTreeWidgetItem *parent);
    void set_item(QString *name, int level, bool is_dir, QTreeWidgetItem *item = nullptr, QTreeWidgetItem *parent = nullptr);
    void add_item(QString *name, int level, bool is_dir, QTreeWidgetItem *parent = nullptr);
    void remove_element(QString &name, int level, bool is_dir);
    void clear();
};

#endif // PROJECTTREEDATA_H
