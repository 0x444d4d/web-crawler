#ifndef ACTOR_H
#define ACTOR_H

#include <functional>
#include <memory>

#include <QObject>
#include <QString>
#include <QVariant>
#include <QTimer>

#include <actors_global.h>
#include <actormanager.h>


class ActorThread;

template <typename Message>
class Mailbox;

class ACTORS_EXPORT Actor : public QObject
{
    Q_OBJECT

public:

    const bool DEL_TIMER = true;
    const bool NO_DEL_TIMER = false;
    using ActorMessage = std::function<void()>;
    using ActorMailbox = Mailbox<ActorMessage>;

    ~Actor();
    bool isStopped();

protected:
    explicit Actor(Actor *parent);

    Actor *sender() { return sender_; }

    bool send(Actor* receiver, const QString& message, const QVariant& arg0=QVariant(),
                                const QVariant& arg1=QVariant(), const QVariant& arg2=QVariant(), 
                                const QVariant& arg3=QVariant(), const QVariant& arg4=QVariant(), 
                                const QVariant& arg5=QVariant(), const QVariant& arg6=QVariant(), 
                                const QVariant& arg7=QVariant(), const QVariant& arg8=QVariant(), 
                                const QVariant& arg9=QVariant());

    bool reply(const QString& message, const QVariant& arg0=QVariant(),
                                const QVariant& arg1=QVariant(), const QVariant& arg2=QVariant(), 
                                const QVariant& arg3=QVariant(), const QVariant& arg4=QVariant(), 
                                const QVariant& arg5=QVariant(), const QVariant& arg6=QVariant(), 
                                const QVariant& arg7=QVariant(), const QVariant& arg8=QVariant(), 
                                const QVariant& arg9=QVariant());


    template <typename ActorClass>
    ActorClass* spawn();

    QTimer* setTimer(QString id, QString message ,std::chrono::milliseconds msec = std::chrono::milliseconds(30000));
    void stopTimer();
    void resetTimer();
    void kill();

public Q_SLOTS:
    void notifyTimeout();

private: 

    std::unique_ptr<ActorMailbox> mailbox_;
    Actor *sender_ = nullptr;
    ActorThread *thread_;
    std::atomic_bool done_;
    QTimer * timer_;
    QString tOutMessage_;
    QString tOutCall_;

    bool delivery_from(Actor* sender, const QString& message, const QVariant& arg0=QVariant(),
                                const QVariant& arg1=QVariant(), const QVariant& arg2=QVariant(),
                                const QVariant& arg3=QVariant(), const QVariant& arg4=QVariant(),
                                const QVariant& arg5=QVariant(), const QVariant& arg6=QVariant(),
                                const QVariant& arg7=QVariant(), const QVariant& arg8=QVariant(),
                                const QVariant& arg9=QVariant());

    bool processMessage();

    friend ActorThread;
    friend ActorManager;
};

template <typename ActorClass>
ActorClass *Actor::spawn()
{
    return ActorManager::instance()->spawn<ActorClass>(this);
}

#endif // ACTOR_H
