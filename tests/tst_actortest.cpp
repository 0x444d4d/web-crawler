#include <QtTest>
#include <QCoreApplication>
#include <iostream>

#include <actor.h>
#include <actormanager.h>
#include "testactor.h"

// add necessary includes here

class actortest : public QObject
{
    Q_OBJECT

public:
    actortest();
    ~actortest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void updateCharProperty();
    void slotIsCalledWhenMessageIsSent();
    void actorCanReply();
    void senderIsNull();
    void senderIsSetWhenMessageArrives();
    void actorKillsItselfWhenRequested();
    void ActorIsNotifiedWhenChildFails();

    /*TODO:
    Actor::unknownMessage(const QString& message);
    void slotIsCalledWhenMessageIsUnknown();
    */

private:
    TestActor* actorA_;
    TestActor* actorB_;
    
};

actortest::actortest()
{

}

actortest::~actortest()
{

}

void actortest::initTestCase()
{
    ActorManager::makeActorManager(this);
    actorA_ = ActorManager::spawn<TestActor>();
    actorB_ = ActorManager::spawn<TestActor>();
}

void actortest::cleanupTestCase()
{
    QPointer<TestActor> p = actorA_;

    ActorManager::kill(actorA_);
    ActorManager::kill(actorB_);

}

void actortest::slotIsCalledWhenMessageIsSent()
{
    int arg = 10;
    QVERIFY(actorA_->testSend(actorB_, "updateIntProperty", arg));
    QTest::qWait(100);
    QVERIFY(actorB_->property("intProperty").canConvert<int>());
    QCOMPARE(actorB_->property("intProperty").toInt(), arg);
}

void actortest::actorCanReply()
{
    connect(actorB_, &TestActor::senderChanged, this, [this](Actor* sender) {
        int arg = 10;
        QVERIFY(actorB_->testReply("updateIntProperty", arg));
        actorB_->disconnect();
    });
    QTest::qWait(1000);
}

void actortest::senderIsNull()
{
    QCOMPARE(actorA_->getSender(), nullptr);
}


void actortest::senderIsSetWhenMessageArrives()
{
    QVERIFY(actorA_->testSend(actorB_, "test"));
    connect(actorB_, &TestActor::senderChanged, this, [this](Actor* sender) {
        QCOMPARE(actorA_, sender);
        actorB_->disconnect();
    });
    QTest::qWait(1000);
    QCOMPARE(actorB_->getSender(), nullptr);
}


void actortest::actorKillsItselfWhenRequested()
{
    QPointer<TestActor> actor = ActorManager::spawn<TestActor>();

    QVERIFY(actor->testSend(actor, "die"));
    QTest::qWait(100);
    QVERIFY(actor.isNull());
}

void actortest::ActorIsNotifiedWhenChildFails()
{
    auto child = actorA_->spawnChildActorAndFail();
    auto cleanup = qScopeGuard([child]() {
        ActorManager::kill(child);
    });
}

void actortest::updateCharProperty()
{
    char arg = 'a';
    QVERIFY(actorA_->testSend(actorB_, "updateCharacter", arg));
    QTest::qWait(100);
    QCOMPARE(actorB_->property("character").toChar(), arg);
}

QTEST_MAIN(actortest)

#include "tst_actortest.moc"
