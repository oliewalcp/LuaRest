#include "Parser.h"
#include "AssistLogic/ExecuteThread.h"

Parser *Parser::_S_parser = new Parser();

Parser::Parser()
{
    moveToThread(ExecuteThread::parser_thread());
}
