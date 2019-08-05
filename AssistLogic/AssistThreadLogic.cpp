#include "AssistThreadLogic.h"
#include "Data/DirectoryData.h"
#include "Data/ProjectTreeData.h"
#include "ExecuteThread.h"
#include "ParserMachine/Parser.h"
#include <QDir>
#include <QFileInfo>
#include <stack>

ExecuteThread *ExecuteThread::_S_assist_thread = new ExecuteThread();
ExecuteThread *ExecuteThread::_S_parser_thread = new ExecuteThread();

AssistThreadLogic *AssistThreadLogic::_S_assist_logic = new AssistThreadLogic();

AssistThreadLogic::AssistThreadLogic() : _M_working(false)
{
    moveToThread(ExecuteThread::assist_thread());
}

void AssistThreadLogic::load_directory_tree_slot(std::shared_ptr<QString> ptr)
{
    DirectoryData::instance()->set_working_space(*ptr);
    load_directory(*ptr);
}

void AssistThreadLogic::load_directory(const QString &dir, int level)
{
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
        ProjectTreeData::instance()->add_item(dire_name, level + 1, true, parent);
        emit add_tree_node_signal(dire_name, dt->flag());
        load_directory(std::forward<QString>(name), level + 1);
        direc.pop();
        dt->reset();
        delete dt;
    }
}
