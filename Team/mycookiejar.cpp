#include "mycookiejar.h"

MyCookieJar::MyCookieJar()
{

}

QList<QNetworkCookie> MyCookieJar::getAllCookies() {return allCookies();}
