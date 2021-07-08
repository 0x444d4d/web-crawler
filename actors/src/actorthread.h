#ifndef ACTORTHREAD_H
#define ACTORTHREAD_H

#include <QThread>

#include <actor.h>

class ActorThread : public QThread
{
    Q_OBJECT
public:
    ActorThread(Actor* actor);

    virtual void run() override;

private:
    Actor *actor_;
};

#endif // ACTORTHREAD_H
