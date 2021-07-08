#include "crawlserver.h"
#include <QDebug>

CrawlServer::CrawlServer(Actor* parent)
    : Actor(parent)
{
    id_ = 0;

}

uint64_t CrawlServer::crawlRequest(const QUrl &url, int depth)
{
    //TODO: check if url is being attended. If so add client for the result
    //If not, create LinkChecker to process the URL.
    qDebug() << "crawlRequest called remotely";
    if (results_.contains(url))
    {
    } else
    {
        linkCheckerList_.append(ActorManager::spawn<LinkChecker>(this));
        send(linkCheckerList_.last(), "request", url, depth, QVariant::fromValue(static_cast<void*>(this)));
    }

}

void CrawlServer::resultReturn(const QUrl &requestUrl, const QList<QUrl> &urlList, bool timeout)
{
    //TODO: Give the list to the pending client's petitions
    //Message CrawlServer(usrl, links);
    QString message = "Called crawlserver result";
    if (timeout)
        message += " after a timeout";
    qDebug() << message;

    for (auto url : urlList)
        qDebug() << "crawl" << url;
    Q_EMIT response(requestUrl, urlList);
}

void CrawlServer::done(const QUrl &requestedUrl)
{
    Q_EMIT response(requestedUrl, results_[requestedUrl]);
}
