#ifndef WEATHERCLASS_H
#define WEATHERCLASS_H

#include <QWidget>
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
#include <QScriptValueIterator>
#include <QXmlStreamReader>
#include <QObject>
#include <iostream>
#include <QVector>
#include <QString>
#include <QImage>
using namespace std;
namespace Ui {
class weatherclass;
}

class weatherclass : public QWidget
{
    Q_OBJECT

public:
    explicit weatherclass(QWidget *parent = nullptr);
    QString getpm10Value24vector();
    ~weatherclass();
private slots:
    //    void on_pushButton_clicked();
        void managerFinished(QNetworkReply *reply);


private:
    Ui::weatherclass *ui;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QXmlStreamReader *reader;
    QVector<QString> pm10Value24vector;
    QVector<QString> pm10Gradevector;




};

#endif // WEATHERCLASS_H
