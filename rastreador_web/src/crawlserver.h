#ifndef CRAWLSERVER_H
#define CRAWLSERVER_H

#include <actor.h>
#include <QMap>
#include <QUrl>

#include "linkchecker.h"

class CrawlServer : public Actor
{
    Q_OBJECT
public:
    explicit CrawlServer(Actor* parent);

public Q_SLOTS:
    uint64_t crawlRequest(const QUrl& url, int depth);
    void resultReturn(const QUrl &requestUrl, const QList<QUrl> &url, bool timeout);
    void done(const QUrl &requestUrl);

Q_SIGNALS:
    void response(const QUrl &originalUrl ,const QList<QUrl> &urlList);

private:
    QMap <QUrl, QList<QUrl>> results_;
    QList<LinkChecker *> linkCheckerList_;
    uint64_t id_ = 0;

};

#endif // CRAWLSERVER_H
