#ifndef ACTORMANAGER_H
#define ACTORMANAGER_H

#include <QVariant>
#include <QtWidgets/QApplication>

#include "actors_global.h"

class Actor;

class ACTORS_EXPORT ActorManager : public QObject
{
    Q_OBJECT
public:
    static ActorManager* makeActorManager(QObject *parent=nullptr);
    static ActorManager* instance();
    ~ActorManager(); 

    template <typename ActorClass>
    static ActorClass* spawn(Actor* parent=nullptr);

    static void kill(Actor* actor);

    static bool send(Actor* receiver, const QString& message, const QVariant& arg0=QVariant(),
                                const QVariant& arg1=QVariant(), const QVariant& arg2=QVariant(),
                                const QVariant& arg3=QVariant(), const QVariant& arg4=QVariant(), 
                                const QVariant& arg5=QVariant(), const QVariant& arg6=QVariant(), 
                                const QVariant& arg7=QVariant(), const QVariant& arg8=QVariant(),
                                const QVariant& arg9=QVariant());

signals:


private:
    explicit ActorManager(QObject *parent = nullptr);
    QScopedPointer<Actor, QScopedPointerDeleteLater> rootActor_;

    static ActorManager *instance_;

};

template <typename ActorClass>
ActorClass *ActorManager::spawn(Actor *parent)
{
    static_assert(std::is_base_of<Actor, ActorClass>::value);
    auto actor = new ActorClass(nullptr);
    actor->moveToThread(QApplication::instance()->thread());
    actor->setParent(parent);

    return actor;
    //return new ActorClass(parent == nullptr ? instance_->rootActor_.get() : parent);

}
#endif // ACTORMANAGER_H
