#include "cauclass.h"
#include "ui_cauclass.h"


#include <QWidget>
#include <QMainWindow>
#include <QGuiApplication>
#include <QApplication>
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtScript/QScriptEngine>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QNetworkCookieJar>
#include <QUrl>
#include <QByteArray>
#include <QEvent>
#include <QXmlStreamReader>
#include <QObject>
#include <QVector>
#include <QString>

#include <iostream>
#include <QUrlQuery>



using namespace std;

cauclass::cauclass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cauclass)
{
        ui->setupUi(this);
        this->setWindowTitle("Login");



}

void cauclass::managerFinished(QNetworkReply *reply)
{
    if (reply->error()) {

        qDebug() << reply->errorString();
        return;
    }

     answer = reply->readAll();
    qDebug() <<answer;

     header= reply->rawHeader("location");
    answer="<html1>"+answer+"</html1>";

    reader = new QXmlStreamReader(answer);
    qDebug() <<header;


    managersecond=new QNetworkAccessManager();
    QObject::connect(managersecond, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinishedSecond(QNetworkReply*)));

    requestsecond.setUrl(QUrl(header));
    managersecond->get(requestsecond);


}

void cauclass::managerFinishedSecond(QNetworkReply *replysecond)
{

 answersecond = replysecond->readAll();

  answersecond="<html>"+answersecond+"</html>";
  reader = new QXmlStreamReader(answersecond);
    std::cout<<"a";




  while(!reader->atEnd() && !reader->hasError())
 {
      while(reader->readNextStartElement())
        {
            if(reader->name() == "input")
            {

                foreach(const QXmlStreamAttribute &attr, reader->attributes())
                {
                    if (attr.name().toString() == QLatin1String("name"))
                    {
                        name = attr.value().toString();
                    }
                    else if(attr.name().toString() == QLatin1String("value"))
                     {
                           value = attr.value().toString();

                     }
                            maps.insert(name,value);


                }

             }

        }
  }



         managerthird=new QNetworkAccessManager();
         QObject::connect(managerthird, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinishedThird(QNetworkReply*)));

         requestthird.setUrl(QUrl("https://eclass3.cau.ac.kr/login/canvas"));

         requestthird.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
         QByteArray headertobyte=header.toUtf8();

         requestthird.setRawHeader("Referer",headertobyte);


          foreach(const QString &key, maps.keys())
          {
              adder+=key+"="+maps.value(key)+"&";

          }

          cookieJar = new MyCookieJar;
          managerthird->setCookieJar(cookieJar);
         managerthird->post(requestthird,adder.toUtf8());



}
 void cauclass::managerFinishedThird(QNetworkReply *replythird)
{
     QList<QNetworkCookie> ck = cookieJar->getAllCookies();
     QByteArray a;
     QByteArray nv;

     answerthird = replythird->readAll();


      ck1 = ck[0].toRawForm(ck[0].NameAndValueOnly);
      ck2 = ck[1].toRawForm(ck[1].NameAndValueOnly);
      ck3 = ck[2].toRawForm(ck[2].NameAndValueOnly);

      header2= replythird->rawHeader("location");

      managerfour=new QNetworkAccessManager();

     QObject::connect(managerfour, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinishedFour(QNetworkReply*)));
     requestfour.setUrl(QUrl(header2));

     requestfour.setRawHeader("cookie",  (ck1 + ";" + ck2 + ";" + ck3).toUtf8() );
     requestfour.setRawHeader("referer",header.toUtf8());

     managerfour->get(requestfour);
}
 void cauclass::managerFinishedFour(QNetworkReply *replyfour)
{
     answerfour = replyfour->readAll();
    qDebug() << answerfour;

     QDate forurl = QDate::currentDate();
     QList<QString> cs;
     QString userid;
     QString url = "https://eclass3.cau.ac.kr/api/v1/calendar_events?type=assignment&context_codes%5B%5D=";
     QRegularExpression reA("course_[0-9]*");

     QRegularExpressionMatchIterator i = reA.globalMatch(answerfour);
     while (i.hasNext())
     {
         QRegularExpressionMatch match = i.next();
         if (match.hasMatch()) {
              cs.push_back(match.captured(0));
         }
     }

     reA.setPattern("user_[0-9][0-9][0-9][0-9]*");
     i = reA.globalMatch(answerfour);
     QRegularExpressionMatch match = i.next();
     userid = match.captured(0);
     url = url+userid+"&";
     for(int i = ((cs.length()/3)*2) ; i<cs.length(); i++){
         url = url+"context_codes%5B%5D="+cs.at(i)+"&";
     }
     forurl = forurl.addMonths(-1);
     url = url+"start_date="+forurl.toString("yyyy-MM-dd")+"T15%3A00%3A00.000Z&end_date=";
     forurl = forurl.addMonths(2);
     url = url+forurl.toString("yyyy-MM-dd")+"T15%3A00%3A00.000Z&per_page=50";

    managerfive =new QNetworkAccessManager();

    QObject::connect(managerfive, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinishedFive(QNetworkReply*)));
    requestfive.setUrl(QUrl(url));
    requestfive.setRawHeader("cookie",  (ck1 + ";" + ck2 + ";" + ck3).toUtf8() );
    QString a = "https://eclass3.cau.ac.kr/calendar";
    requestfive.setRawHeader("referer", a.toUtf8());
    managerfive->get(requestfive);



}

 void cauclass::managerFinishedFive(QNetworkReply *replyfour)
{
     cout << "asdaf" << endl;

     QString answerfive = replyfour->readAll();
     answerfive=answerfive.remove(0,9);
     qDebug()<<answerfive;
          QByteArray data = answerfive.toUtf8();
            QJsonDocument json_doc = QJsonDocument::fromJson(data);
              foreach (QJsonValue var, json_doc.array())
              {
                  title.push_back(var.toObject().value("title").toString());
                  end.push_back(var.toObject().value("end_at").toString().remove(10,10));

              }

              for(int i = 0; i < title.length(); i++){
                  qDebug() << title.at(i);
                  qDebug() << end.at(i);
              }


           temp = 1;

           schedule = new Calendar();
           schedule->dateColor(title, end);
           schedule->show();
}

int cauclass::gettemp(){
    return temp;
}

// QList<QString> cauclass::getass(){
//     return title;
// }

// QList<QString> cauclass::getend(){
//     return end;
// }
cauclass::~cauclass()
{
    delete ui;
}

void cauclass::on_pushButton_clicked()
{
    hide();
    user=ui->txtname->text();
    std=ui->txtstd->text();
    QByteArray name_Q = QUrl::toPercentEncoding(user);
    QByteArray  std_Q= QUrl::toPercentEncoding(std);
    qDebug()<<name_Q;
    qDebug()<<std_Q;


  Array ="user_id="+std_Q+"&user_name="+name_Q+"&user_type=1&dept_group=%EC%BB%B4%ED%93%A8%ED%84%B0%EA%B3%B5%ED%95%99";

    manager=new QNetworkAccessManager();
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply*)));

    request.setUrl(QUrl("https://ocs2.cau.ac.kr/index.php?module=xn_sso2013&act=procXn_sso2013ExternalLoginCallback&return_url=https%3A%2F%2Feclass3.cau.ac.kr%2F%2Flearningx%2Flogin&from=web_redirect&login_type=sso"));

    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
     manager->post(request,Array);

}
