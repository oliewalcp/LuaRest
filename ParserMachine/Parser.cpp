#include "Parser.h"
#include "AssistLogic/ExecuteThread.h"
#include "Actor.h"
#include <fstream>
#include <set>
#include <QDebug>

Parser *Parser::_S_parser = nullptr;

typedef std::set<std::string> KeywordContainer;

static const char* KEYWORD_FILE = "config/keyword.txt";
static KeywordContainer *KeywordSet = nullptr;

Parser::Parser()
{
    KeywordSet = new KeywordContainer();
    moveToThread(ExecuteThread::parser_thread());
    _F_read_config();
}

Parser::~Parser()
{
    if(KeywordSet != nullptr)
    {
        delete KeywordSet;
    }
}

Parser *Parser::instance()
{
    if(_S_parser == nullptr)
        _S_parser = new Parser();
    return _S_parser;
}
/* 解析文件
 * param[filename]:文件名 need delete
 */
void Parser::new_file_slot(QString *filename)
{
    Actor::instance()->parse(filename);
}

void Parser::_F_read_config()
{
    std::ifstream f(KEYWORD_FILE);
    while(true)
    {
        std::string temp;
        f >> temp;
        if(f.eof())
            break;
        KeywordSet->insert(temp);
    }
}

bool Parser::_F_is_keyword(const std::string &word)
{
    return KeywordSet->find(word) != KeywordSet->end();
}

