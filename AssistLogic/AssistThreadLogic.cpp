#include "AssistThreadLogic.h"
#include "Data/DirectoryData.h"
#include "Data/ProjectTreeData.h"
#include "ParserMachine/Parser.h"
#include "ExecuteThread.h"
#include <QDir>
#include <QFileInfo>
#include <stack>
#include <QDebug>

AssistThreadLogic *AssistThreadLogic::_S_assist_logic = nullptr;

AssistThreadLogic::AssistThreadLogic() : _M_working(false)
{
    moveToThread(ExecuteThread::assist_thread());
}

const AssistThreadLogic *AssistThreadLogic::instance()
{
    if(_S_assist_logic == nullptr)
        _S_assist_logic = new AssistThreadLogic();
    return _S_assist_logic;
}

void AssistThreadLogic::load_directory_tree_slot(std::shared_ptr<QString> ptr)
{
    qDebug() << __FILE__ << ":" << __func__ << ":" << __LINE__ << "\n" << tr("start load ") << *ptr;
    DirectoryData::instance()->set_working_space(*ptr);
    load_directory(*ptr);
}

void AssistThreadLogic::load_directory(const QString &dir, int level)
{
    qDebug() << __FILE__ << ":" << __func__ << ":" << __LINE__ << "\n" << tr("load ") << dir;
    static std::stack<ItemDataType *> direc;
    QDir directory(dir);
    QStringList lua_files;
    QFileInfoList &&dir_list = directory.entryInfoList(lua_files, QDir::Dirs);//所有文件夹
    lua_files.append(tr("*.[lL]{1}[Uu]{1}[aA]{1}"));
    QFileInfoList &&file_list = directory.entryInfoList(lua_files, QDir::Files);//所有.lua文件
    for(auto it = dir_list.begin(); it != dir_list.end(); ++it)
    {
        QFileInfo &file_info = *it;
        QString &&name = file_info.fileName();
        if(name == "." || name == "..") continue;
        // 由于与ProjectTreeData共享指针，所有这里不要释放dire_name，dire_name在ProjectTreeData释放
        QString *dire_name = new QString(name);
        QTreeWidgetItem *parent = nullptr;
        if(direc.size() > 0)
        {
            parent = direc.top()->parent();
        }
        ItemDataType *dt = new ItemDataType(dire_name, level, true, parent);
        direc.push(dt);
        qDebug() << __FILE__ << ":" << __func__ << ":" << __LINE__ << "\n" << "ready send signal ";
        ProjectTreeData::instance()->add_item(dire_name, level + 1, true, parent);
        qDebug() << __FILE__ << ":" << __func__ << ":" << __LINE__ << "\n" << "send signal ";
        emit add_tree_node_signal(dire_name, dt->flag());
        load_directory(std::forward<QString>(name), level + 1);
        direc.pop();
        dt->reset();
        delete dt;
    }
}
