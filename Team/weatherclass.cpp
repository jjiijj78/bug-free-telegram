#include "weatherclass.h"
#include "ui_weatherclass.h"

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

using namespace std;
weatherclass::weatherclass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::weatherclass)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(255, 255, 255, 255));
    setAutoFillBackground(true);
    setPalette(palette);
    this->setWindowTitle("CAU Fine Dust");

    manager=new QNetworkAccessManager();
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),
    this, SLOT(managerFinished(QNetworkReply*)));
    request.setUrl(QUrl("http://openapi.airkorea.or.kr/openapi/services/rest/ArpltnInforInqireSvc/getMsrstnAcctoRltmMesureDnsty?stationName=%EB%8F%99%EC%9E%91%EA%B5%AC&dataTerm=month&pageNo=1&numOfRows=10&ServiceKey=aO8EOC%2FgfNOmA2xNmqnUZ7SVSsccrWDUcyntBCOnPOrBgARMMUY87ZP2nGc8qiiZFY9l5jr53xAL9e5CQKIcww%3D%3D&ver=1.3"));
    manager->get(request);

}
//QString weatherclass::getpm10Value24vector()
//{
//    QString temp = pm10Value24vector.at(0);
//    return temp;

//}

//    void weather::on_pushButton_clicked()
//    {
//        request.setUrl(QUrl("http://openapi.airkorea.or.kr/openapi/services/rest/ArpltnInforInqireSvc/getMsrstnAcctoRltmMesureDnsty?stationName=%EB%8F%99%EC%9E%91%EA%B5%AC&dataTerm=month&pageNo=1&numOfRows=10&ServiceKey=aO8EOC%2FgfNOmA2xNmqnUZ7SVSsccrWDUcyntBCOnPOrBgARMMUY87ZP2nGc8qiiZFY9l5jr53xAL9e5CQKIcww%3D%3D&ver=1.3"));
//        manager->get(request);

//    }
    void weatherclass::managerFinished(QNetworkReply *reply)
    {
        if (reply->error()) {
            qDebug() << reply->errorString();
            return;
        }

        QString answer = reply->readAll();
        reader = new QXmlStreamReader(answer);
        qDebug()<< reader;

        while(!reader->atEnd() && !reader->hasError())
       {
            if(reader->readNext() == QXmlStreamReader::StartElement)
            {
                if(reader->name() == "pm10Value")
                {
                pm10Value24vector.append(reader->readElementText());
                        }

                 else if(reader->name() == "pm10Grade")
                 {
                    pm10Gradevector.append(reader->readElementText());
                 }
                 else
                 {
                    continue;
                 }
            }
        }

        int width;
        int height;
        QString state;
       if(pm10Gradevector[0].toInt()==1)
       {
           QPixmap pix("/home/mose/Team/image/happy.png");
           width= ui->pm10grade->width();
           height= ui->pm10grade->height();
            ui->pm10grade->setPixmap(pix.scaled(width,height,Qt::KeepAspectRatio));
            state ="좋음";
       }
       else if(pm10Gradevector[0].toInt()==2)
       {
           QPixmap pix("/home/mose/Team/image/surprised.png");
            width= ui->pm10grade->width();
            height= ui->pm10grade->height();
             ui->pm10grade->setPixmap(pix.scaled(width,height,Qt::KeepAspectRatio));
             state ="보통";
       }
       else if(pm10Gradevector[0].toInt()==3)
       {
           QPixmap pix("/home/mose/Team/image/sad.png");
            width= ui->pm10grade->width();
            height= ui->pm10grade->height();
            ui->pm10grade->setPixmap(pix.scaled(width,height,Qt::KeepAspectRatio));
            state ="나쁨";
       }
       else
       {
           QPixmap pix("/home/mose/Team/image/devil.png");
            width= ui->pm10grade->width();
            height= ui->pm10grade->height();
        ui->pm10grade->setPixmap(pix.scaled(width,height,Qt::KeepAspectRatio));
        state ="아주나쁨";
       }


    ui->pm10gradetxt->setText("중앙대 미세먼지 상태는 "+state+"입니다");
    ui->pm10Value24->setText("중앙대 미세먼지 농도는 "+pm10Value24vector.at(0)+"입니다");


    }


weatherclass::~weatherclass()
{
    delete ui;
}
