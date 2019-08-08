#include "Actor.h"
#include "Parser.h"
#include <QString>

Actor* Actor::_S_actor = new Actor();

/* 解析文件
 * param[filename]:文件名 need delete
 */
void Actor::parse(QString *filename)
{
    delete filename;
}
