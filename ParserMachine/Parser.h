#ifndef PARSER_H
#define PARSER_H

#include <QObject>

class Parser : public QObject
{
    Q_OBJECT
private:
    static Parser *_S_parser;

    Parser();
public:
    static Parser* instance()
    { return _S_parser; }
};

#endif // PARSER_H
