#ifndef LINKCHECKER_H
#define LINKCHECKER_H

#include <actor.h>
#include <QSet>
#include <QUrl>
#include <QTimer>



class LinkChecker : public Actor
{
    Q_OBJECT
public:
    const bool TIMEOUT_OCCURRED = true;
    const bool TIMEOUT_NOT_OCCURRED = false;
    explicit LinkChecker(Actor* parent);

public Q_SLOTS:
    void request(const QUrl& url, int depth, void *crawler);
    void getUrls(const QUrl& url, int depth);
    void checkUrl(const QUrl& url, int depth);
    void done();
    void timeout(QString message);

private:
    Actor *crawler_;
    QTimer* timer_;
    QSet<QUrl> urlSet;
    QList<Actor *> getters_;
    std::atomic<int64_t> GetterCounter;
    QUrl originalUrl;


};

#endif // LINKCHECKER_H
