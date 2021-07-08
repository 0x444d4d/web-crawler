#include <QDebug>
#include <iostream>

#include <actor.h>
#include "mailbox.h"
#include "actorthread.h"

Actor::Actor(Actor* parent) : QObject(parent), done_(false)
{
    mailbox_ = std::make_unique<ActorMailbox>();
    thread_ = new ActorThread(this);
    thread_->start();
}

Actor::~Actor()
{
    if (!thread_->isFinished())
        qCritical() << "Se ha intentado destruir un actor no detenido: " << this;
}

bool Actor::delivery_from(Actor * sender, const QString& message, const QVariant& arg0,
                                const QVariant& arg1, const QVariant& arg2, const QVariant& arg3, const QVariant& arg4, 
                                const QVariant& arg5, const QVariant& arg6, const QVariant& arg7, const QVariant& arg8, 
                                const QVariant& arg9)
{
    mailbox_->push([this, sender, message, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9]() {

        sender_ = sender;

        bool success = QMetaObject::invokeMethod(this, message.toLocal8Bit(), Qt::DirectConnection,
                                QGenericArgument(arg0.typeName(), arg0.data()),
                                QGenericArgument(arg1.typeName(), arg1.data()),
                                QGenericArgument(arg2.typeName(), arg2.data()),
                                QGenericArgument(arg3.typeName(), arg3.data()),
                                QGenericArgument(arg4.typeName(), arg4.data()),
                                QGenericArgument(arg5.typeName(), arg5.data()),
                                QGenericArgument(arg6.typeName(), arg6.data()),
                                QGenericArgument(arg7.typeName(), arg7.data()),
                                QGenericArgument(arg8.typeName(), arg8.data()),
                                QGenericArgument(arg9.typeName(), arg9.data()));
        sender_ = nullptr;

    });

    return true;
}


bool Actor::send(Actor* receiver, const QString& message, const QVariant& arg0,
                                const QVariant& arg1, const QVariant& arg2, const QVariant& arg3, const QVariant& arg4, 
                                const QVariant& arg5, const QVariant& arg6, const QVariant& arg7, const QVariant& arg8, 
                                const QVariant& arg9)
{
    return receiver->delivery_from(this, message, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);

}

bool Actor::reply(const QString& message, const QVariant& arg0,
                                const QVariant& arg1, const QVariant& arg2, const QVariant& arg3, const QVariant& arg4, 
                                const QVariant& arg5, const QVariant& arg6, const QVariant& arg7, const QVariant& arg8, 
                                const QVariant& arg9)
{
    if (sender_)
        return send(sender_, message, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
    return false;
}

QTimer* Actor::setTimer(QString id, QString message, std::chrono::milliseconds msec)
{
    if (timer_ != nullptr)
    {
        return timer_;
    }

    tOutCall_ = id;
    tOutMessage_ = message;
    timer_ = new QTimer(nullptr);
    timer_->setInterval(msec);
    timer_->start();
    timer_->moveToThread(this->thread());
    connect(timer_, &QTimer::timeout, this, &Actor::notifyTimeout);

    return timer_;
}

void Actor::notifyTimeout()
{
    qDebug() << "timeout";
    send(this, 0, tOutCall_, tOutMessage_);
}

void Actor::stopTimer()
{

    if (timer_ == nullptr)
        return;
    else
    {
        timer_ = nullptr;
    }
}

void Actor::resetTimer()
{
    if (timer_ != nullptr)
    {
        timer_ = nullptr;
        setTimer(tOutCall_, tOutMessage_, timer_->intervalAsDuration());
    }

}



void Actor::kill()
{
    done_ = true;
    thread_->terminate();
}

bool Actor::processMessage()
{
    auto message = mailbox_->pop(std::chrono::milliseconds(100));
    if (!done_ && message)
    {
        std::invoke(message.value());
    }
    return !done_;
}
