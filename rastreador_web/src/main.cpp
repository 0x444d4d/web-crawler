#include <QCoreApplication>

#include <actormanager.h>
#include <actor.h>
#include <QRemoteObjectHost>
#include <QRemoteObjectRegistryHost>

#include "indexingservice.h"

const auto REMOTE_OBJECT_NAME = QStringLiteral("local:indexing-service");
const auto REMOTE_OBJECT_REGISTRY = QStringLiteral("local:registry");


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    IndexingService indexingService;

    QRemoteObjectRegistryHost registryNode(REMOTE_OBJECT_REGISTRY);
    QRemoteObjectHost indexingServiceNode(REMOTE_OBJECT_NAME, REMOTE_OBJECT_REGISTRY);

    ActorManager::makeActorManager();
    indexingServiceNode.enableRemoting(&indexingService);

    return a.exec();
}
