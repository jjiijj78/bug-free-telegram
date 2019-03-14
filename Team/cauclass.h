#ifndef CAUCLASS_H
#define CAUCLASS_H

#include <QWidget>
#include "mycookiejar.h"

#include <QMainWindow>
#include <QGuiApplication>
#include <QApplication>
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtScript/QScriptEngine>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QByteArray>
#include <QEvent>
#include <QtNetwork/QNetworkCookieJar>

#include <QXmlStreamReader>
#include <QObject>
#include <iostream>
#include <QVector>
#include <QList>
#include <QString>
#include <QUrlQuery>
#include <QJsonObject>
#include <QMap>
#include "calendar.h"

using namespace std;
namespace Ui {
class cauclass;
}

class cauclass : public QWidget
{
    Q_OBJECT

public:
    explicit cauclass(QWidget *parent = nullptr);
    QList<QString> getass();
    QList<QString> getend();
    int gettemp();
    ~cauclass();

private:
    Ui::cauclass *ui;
    QNetworkAccessManager *manager;
    QNetworkAccessManager *managersecond;
    QNetworkAccessManager *managerthird;
    QNetworkAccessManager *managerfour;
    QNetworkAccessManager *managerfive;
    QNetworkRequest request;
    QNetworkRequest requestsecond;
    QNetworkRequest requestthird;
    QNetworkRequest requestfour;
    QNetworkRequest requestfive;
    QXmlStreamReader *reader;
    QByteArray Array;
    QByteArray Arraysecond;
    QUrlQuery postData;
    QUrl params;
    QJsonObject json;
    QVector<QString> href;
    QString answer;
    QString answersecond;
    QString answerthird;
     QString answerfour;
    QString adder;
    QString header;
    QString header2;
    QMap<QString,QString> maps;
    QString name;
    QString value;
    MyCookieJar *cookieJar;
    QString ck1, ck2, ck3;
    QList<QString> title, end;
    QString  user, std;
    int temp=0;
    Calendar *schedule;



private slots:

        void managerFinished(QNetworkReply *reply);
         void managerFinishedSecond(QNetworkReply *replysecond);
          void managerFinishedThird(QNetworkReply *replythird);
           void managerFinishedFour(QNetworkReply *replyfour);
           void managerFinishedFive(QNetworkReply *replyfour);

           void on_pushButton_clicked();
};

#endif // CAUCLASS_H
