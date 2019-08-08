#ifndef PARSER_H
#define PARSER_H

#include <QObject>

class Parser final : public QObject
{
    Q_OBJECT
private:
    static Parser *_S_parser;

    Parser();

    void _F_read_config();
    bool _F_is_keyword(const std::string &word);
public:
    ~Parser();
    static Parser* instance()
    { return _S_parser; }

    bool is_keyword(const std::string &word)
    { return _F_is_keyword(word); }
    bool is_keyword(std::string &&word)
    { return _F_is_keyword(std::forward<std::string>(word)); }
    bool is_keyword(const char* word)
    { return _F_is_keyword(std::forward<std::string>(std::string(word))); }

public slots:
    void new_file_slot(QString *filename);
};

#endif // PARSER_H
