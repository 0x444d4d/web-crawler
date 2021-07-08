#include "httpgetter.h"
#include "schemapluginmanager.h"
#include <QUrl>
#include <QDebug>

HttpGetter::HttpGetter(Actor *parent)
    :Actor(parent)
{

}

void HttpGetter::request(const QUrl &url, int depth)
{

    auto fetcher =SchemaPluginManager::instance().getSchemaPlugin(url.scheme().toStdString());
    if (!fetcher)
    {
        reply("done");
        kill();
        return;
    }

    auto info = fetcher->fetchUrl(url.toString().toStdString());
    qDebug() << "Url downloaded";


    if (! info)
    {
        reply("done");
        kill();
        return;
    }

    auto results = fetcher->parse(info.value());
    if (!results)
    {
        reply("done");
        kill();
        return;
    }

    for (auto newUrl : results.value())
        reply("checkUrl", url.resolved(QString::fromStdString(newUrl)), depth);

    info.value().content.clear();

    reply("done");
    kill();
}
