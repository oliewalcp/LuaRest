#ifndef ACTOR_H
#define ACTOR_H

class QString;

class Actor
{
private:
    static Actor* _S_actor;

    Actor() { }
public:
    static Actor* instance()
    { return _S_actor; }

    void parse(QString *filename);
};

#endif // ACTOR_H
