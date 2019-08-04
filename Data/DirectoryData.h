#ifndef DirectoryDataDATA_H
#define DirectoryDataDATA_H

#include <QString>

// 为了线程安全，写操作由辅助线程进行
class DirectoryData
{
private:
    DirectoryData() { }
    static DirectoryData *_S_Directory;

    QString _M_working_DirectoryData;
public:
    static DirectoryData* instance() { return _S_Directory; }

    void set_working_space(const QString &dir)
    { _M_working_DirectoryData = dir; }
    void set_working_space(QString &&dir)
    { _M_working_DirectoryData = std::forward<QString>(dir); }
};

#endif // DirectoryDataDATA_H
