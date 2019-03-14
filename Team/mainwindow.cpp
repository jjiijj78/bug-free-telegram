#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QPushButton>
#include <QIcon>
#include <QSize>
#include <QBitmap>
#include <QFileDialog>
#include <QFile>
#include <QtWidgets>
#include <QMenuBar>
#include <QDateTime>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //palet background
    ui->setupUi(this);


    QPalette palette;
    palette.setColor(QPalette::Window, QColor(237,237,237,255));
    setAutoFillBackground(true);
    setPalette(palette);
    this->setWindowTitle("seCAUtary");

    //memo
    QPixmap memopixmap("/home/mose/Team/image/memo_purple.jpg");
    QIcon memoButtonIcon(memopixmap);
    ui->MemoButton->setIcon(memoButtonIcon);
    ui->MemoButton->setIconSize(memopixmap.rect().size());

    //calendar
    QPixmap calendarpixmap("/home/mose/Team/image/calendar_red.png");
    QIcon calendarButtonIcon(calendarpixmap);
    ui->CalendarButton->setIcon(calendarButtonIcon);
    ui->CalendarButton->setIconSize(calendarpixmap.rect().size());

    //alarm
    QPixmap alarmpixmap("/home/mose/Team/image/alarm_green.png");
    QIcon alarmButtonIcon(alarmpixmap);
    ui->AlarmButton->setIcon(alarmButtonIcon);
    ui->AlarmButton->setIconSize(alarmpixmap.rect().size());


     //dust
    QPixmap weatherpixmap("/home/mose/Team/image/dust_brown.png");
    QIcon weatherButtonIcon(weatherpixmap);
    ui->WeatherButton->setIcon(weatherButtonIcon);
    ui->WeatherButton->setIconSize(weatherpixmap.rect().size());



    //cau
    QPixmap caupixmap("/home/mose/Team/image/bluedragon_alarm.jpg");
    QIcon cauButtonIcon(caupixmap);
    ui->CauButton->setIcon(cauButtonIcon);
    ui->CauButton->setIconSize(caupixmap.rect().size());



    //exit
   QPixmap exitpixmap("/home/mose/Team/image/powerset_blue.png");
   QIcon exitButtonIcon(exitpixmap);
   ui->ExitButton->setIcon(exitButtonIcon);
   ui->ExitButton->setIconSize(exitpixmap.rect().size());


   //time
   timer= new QTimer(this);
   connect(timer, SIGNAL(timeout()),this, SLOT(myfunction()));
   timer ->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myfunction()
{
    QTime time = QTime :: currentTime();
    QString time_text = time.toString("hh : mm :ss");

    ui->label_digitalclock->setText(time_text);
    alarm->check_Alarm(time);
}


void MainWindow::on_MemoButton_clicked()
{
    memo = new Memo();
    memo->show();
}

void MainWindow::on_AlarmButton_clicked()
{
    alarm = new Alarm();
    alarm->show();
}

void MainWindow::on_WeatherButton_clicked()
{  weather =new weatherclass();
   //ui->Weather->setText(weather->getpm10Value24vector());
   weather->show();

}

void MainWindow::on_CauButton_clicked()
{
    cau = new cauclass();
    cau->show();


}

void MainWindow::on_CalendarButton_clicked()
{
    calendar = new Calendar();
    calendar->dateColor();
    calendar->show();
}




void MainWindow::on_ExitButton_clicked()
{
    this->close();
}
