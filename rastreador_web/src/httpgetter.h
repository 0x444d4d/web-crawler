#ifndef HTTPGETTER_H
#define HTTPGETTER_H

#include <actor.h>

class HttpGetter : public Actor
{
    Q_OBJECT
public:
    explicit HttpGetter(Actor* parent);

public Q_SLOTS:
    void request(const QUrl& url, int depth);

};

#endif // HTTPGETTER_H
