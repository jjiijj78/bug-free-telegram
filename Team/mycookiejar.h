#ifndef MYCOOKIEJAR_H
#define MYCOOKIEJAR_H

#include <QtNetwork>

class MyCookieJar : public QNetworkCookieJar
{
public:
    MyCookieJar();
    QList<QNetworkCookie> getAllCookies();
};

#endif // MYCOOKIEJAR_H
