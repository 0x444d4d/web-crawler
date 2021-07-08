#include "actorthread.h"

ActorThread::ActorThread(Actor *actor) : QThread(actor), actor_(actor)
{

}

void ActorThread::run()
{
    while(actor_->processMessage());
    actor_->deleteLater();
}
