#ifndef MAILBOX_H
#define MAILBOX_H

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

template <class Message>
class Mailbox
{
public:
    Mailbox() = default;

    void push( const Message& message)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        mailbox_.push(message);
        mailboxNoEmpty_.notify_one();
    }

    void push(Message&& message)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        mailbox_.push(message);
        mailboxNoEmpty_.notify_one();
    }

    std::optional<Message> pop(const std::chrono::milliseconds& rel_time)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        bool noEmpty = mailboxNoEmpty_.wait_for(lock, rel_time, [this] {
            return !mailbox_.empty();
        });
        if (noEmpty) {
            auto message = std::move(mailbox_.front());
            mailbox_.pop();
            return message;
        }
        //return Message();
        return {};
    }
    void clear()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        mailbox_.swap(std::queue<Message>());
    }

    bool isEmpty()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return mailbox_.empty();
    }

private:
    std::queue<Message> mailbox_;
    std::mutex mutex_;
    std::condition_variable mailboxNoEmpty_;
};



#endif // MAILBOX_H
