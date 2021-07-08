#ifndef TESTACTOR_H
#define TESTACTOR_H

#include <iostream>
#include <actor.h>

class TestActor : public Actor
{
    Q_OBJECT
    Q_PROPERTY(int intProperty MEMBER intProperty_)
    Q_PROPERTY(char character MEMBER character_)
public:
    explicit TestActor(Actor *parent): Actor(parent) {}

    bool testSend(Actor *receiver, const QString &message, const QVariant&  arg)
    {
        return send(receiver, message, arg);
    }

    bool testSend(Actor *receiver, const QString &message)
    {
        return send(receiver, message);
    }

    bool testReply(const QString& message, const QVariant& arg)
    {
        return reply(message);
    }

    TestActor* spawnChildActorAndFail()
    {
        auto actor = spawn<TestActor>();
        send(actor, "failedTask");
        return actor;
    }

Q_SIGNALS:
    void senderChanged(Actor* sender);

public Q_SLOTS:
    void updateIntProperty(int arg)
    {
        intProperty_ = arg;
    }

    void updateCharacter(int arg)
    {
        character_ = arg;
    }

    void die()
    {
        kill();
    }

    void test()
    {

    }

    Actor* getSender()
    {
        return this->sender();
    }

private:
    int intProperty_;
    char character_;

};

#endif // TESTACTOR_H
