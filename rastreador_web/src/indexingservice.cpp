#include "indexingservice.h"


IndexingService::IndexingService()
{
    ActorManager::makeActorManager();
    crawler_ = ActorManager::spawn<CrawlServer>();
    connect(crawler_, &CrawlServer::response, this, &IndexingService::result, Qt::QueuedConnection);
}

IndexingService::~IndexingService()
{

}

unsigned IndexingService::request(const QUrl &url, int depth)
{
    ActorManager::send(crawler_, "crawlRequest", url, depth);
    qDebug() << "Called IndexingServiece's request";
}

void IndexingService::result(const QUrl &originalUrl, const QList<QUrl> &urlList)
{
    qDebug() << "Recibida la sennal de crawler";
    Q_EMIT response(originalUrl, urlList);
}
