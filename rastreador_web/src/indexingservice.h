#ifndef REMOTECONNECTION_H
#define REMOTECONNECTION_H

#include <QObject>
#include <QSet>
#include <QUrl>
#include <rep_remoteObject_source.h>
#include <actormanager.h>
#include <actor.h>
#include "crawlserver.h"


class IndexingService : public IndexingServiceSimpleSource
{
    Q_OBJECT

private:

    CrawlServer *crawler_;

public Q_SLOTS:
    void result(const QUrl &originalUrl, const QList<QUrl> &urlList);

public:
    IndexingService();
    ~IndexingService();
    virtual unsigned request(const QUrl &url, int depth);
};

#endif // REMOTECONNECTION_H
