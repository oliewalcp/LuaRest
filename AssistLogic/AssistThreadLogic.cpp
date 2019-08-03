#include "AssistThreadLogic.h"
#include <QDir>
#include <QFileInfo>

AssistThreadLogic *AssistThreadLogic::_S_assist_logic = new AssistThreadLogic();

AssistThreadLogic::AssistThreadLogic() : _M_thread(new ExecuteThread), _M_working(false)
{
    _M_thread->start();
    moveToThread(_M_thread);
}

void AssistThreadLogic::load_directory_tree_slot(std::shared_ptr<QString> ptr)
{

}

void AssistThreadLogic::load_directory(const QString &dir)
{
    QDir directory(dir);
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
