#include "linkchecker.h"
#include <QDebug>
#include <actormanager.h>
#include "httpgetter.h"

LinkChecker::LinkChecker(Actor* parent)
    :Actor(parent), GetterCounter(0)
{

}

void LinkChecker::request(const QUrl &url, int depth, void *crawler)
{
    //Save the original URL and parse the html
    //Create HTTPGetter to process the URL
    qDebug() << "Called LinkChecker's request()";

    crawler_ = static_cast<Actor *>(crawler);

    qDebug() << "Setting timer";
    setTimer("timeout", "Getter timed out" ,std::chrono::milliseconds(10000));

    originalUrl = url;
    getUrls(url, depth);

}

void LinkChecker::getUrls(const QUrl& url, int depth)
{
    //Download the requested url
    qDebug() << "Called getUrls";
    auto getter = ActorManager::spawn<HttpGetter>(this);
    getters_.append(getter);
    send(getter, "request", url, --depth);
    ++GetterCounter;
}

void LinkChecker::checkUrl(const QUrl &url, int depth)
{
    //Ask if the URL has been checked, if so, ignore it.
    //Otherwise create httpgetter with --depth
    //If depth == 0 save URL without processing

    qDebug() << "called checkUrl with " << url << " and depth of " << depth;

    auto size = urlSet.size();
    urlSet.insert(url);
    if (urlSet.size() > size)
    {
        qDebug() << url << " inserted";
        if (depth > 0)
            getUrls(url, depth);
    }
}

void LinkChecker::timeout(QString message)
{
    qDebug() << message;
    for (auto getter : getters_)
        continue;
        //ActorManager::kill(getter);
    QVariant list;
    list.setValue<QList<QUrl>>(urlSet.values());
    send(crawler_, 0,"resultReturn", originalUrl, list, TIMEOUT_OCCURRED);
}

void LinkChecker::done()
{
    //check if it's the last HTTPGetter. If so send URL list to CrawlServer
    //The answer is result()
    qDebug() << "Called Done()";

    stopTimer();
    --GetterCounter;
    if (GetterCounter < 1)
    {
        qDebug() << "Last getter";
        //Give result to CrawlServer
        qDebug() << "Sending URLs to crawlserver";
        QVariant list;
        list.setValue<QList<QUrl>>(urlSet.values());
        send(crawler_, "resultReturn", originalUrl, list, TIMEOUT_NOT_OCCURRED);
    }
    resetTimer();
}
