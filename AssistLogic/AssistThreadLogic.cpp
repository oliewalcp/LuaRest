#include "AssistThreadLogic.h"
#include "Data/DirectoryData.h"
#include "ExecuteThread.h"
#include <QDir>
#include <QFileInfo>

ExecuteThread *ExecuteThread::_S_assist_thread = new ExecuteThread();

AssistThreadLogic *AssistThreadLogic::_S_assist_logic = new AssistThreadLogic();

AssistThreadLogic::AssistThreadLogic() : _M_working(false)
{
    moveToThread(ExecuteThread::assist_thread());
}

void AssistThreadLogic::load_directory_tree_slot(std::shared_ptr<QString> ptr)
{
    DirectoryData::instance()->set_working_space(*ptr);
}

void AssistThreadLogic::load_directory(const QString &dir)
{
    QDir directory(dir);
    QStringList lua_files;
    lua_files.append(tr("*.[lL]{1}[Uu]{1}[aA]{1}"));
    QFileInfoList &&file_list = directory.entryInfoList(lua_files, QDir::Files);//所有.lua文件
    QFileInfoList &&dir_list = directory.entryInfoList();//所有文件夹
    for(auto it = dir_list.begin(); it != dir_list.end(); ++it)
    {
        QFileInfo &file_info = *it;
        QString &&name = file_info.fileName();
        if(name == "." || name == "..") continue;
    }
}
