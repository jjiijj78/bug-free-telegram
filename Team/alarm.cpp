#include "alarm.h"
#include "ui_alarm.h"
#include <iostream>


Alarm::Alarm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Alarm)
{
    ui->setupUi(this);

    this->setWindowTitle("Alarm");

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(237, 237, 237, 255));
    setAutoFillBackground(true);
    setPalette(palette);

    QDir path_dir("/home/mose/Team/alarm/");
    QStringList files = path_dir.entryList(QDir::Files);
    ui->comboBox_3->addItems(files);
    ui->comboBox_3->show();
}

Alarm::~Alarm()
{
    delete ui;
}

void Alarm::on_pushButton_clicked()
{
    date = ui->calendarWidget->selectedDate();
    date.getDate(a,a+1,a+2);
    if(a[5] == 2 && a[3] < 12) a[3] = a[3]+12;
    if(a[5] == 1 && a[3] >= 12) a[3] = a[3]-12;
    for(int i = 0; i<5; i++){
        v.push_back(a[i]);
    }

    QString path = "/home/mose/Team/alarm/";
    QString title;

    for(int i = 0; i < 5; i++){
        if(a[i] < 10) title = title + '0';
        title=title+QString::number(a[i]);

        if(i == 2) title=title+'_';
    }

    QFile file(path + title);

    if(file.open(QFile::WriteOnly | QFile::Text)){
        QTextStream out(&file);

        out << "";

        file.flush();
        file.close();
    }

    QDir path_dir("/home/mose/Team/alarm/");
    QStringList files = path_dir.entryList(QDir::Files);
    ui->comboBox_3->clear();
    ui->comboBox_3->addItems(files);
    ui->comboBox_3->show();
}

void Alarm::on_comboBox_2_currentIndexChanged(int index)
{
    a[3] = index;
}

void Alarm::on_comboBox_currentIndexChanged(int index)
{
    a[5] = index;
}

void Alarm::on_spinBox_valueChanged(int arg1)
{
    a[4] = arg1;
}

QList<int>* Alarm::get_AlarmList(void){
    return &v;
}

void Alarm::check_Alarm(QTime time){

    if(time.second() == 0){
        QDate d = QDate :: currentDate();
        QString path = "/home/mose/Team/alarm/";

        QString title = QString::number(d.year());

        if(d.month() < 10) title=title+'0';
        title=title+QString::number(d.month());

        if(d.day() < 10) title=title+'0';
        title=title+QString::number(d.day());

        title=title+'_';

        if(time.hour() < 10) title=title+'0';
        title=title+QString::number(time.hour());

        if(time.minute() < 10) title=title+'0';
        title=title+QString::number(time.minute());

        QString fileName = path + title;

    if(!fileName.isEmpty()){
        QFile file(fileName);
        if(file.open(QFile::ReadOnly | QFile::Text)){
            QTextStream in(&file);
            QString text = in.readAll();
            file.close();
            sound = new alarm_widget();
            sound->show();
        }
    }

  }

}

void Alarm::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    delete_file = arg1;
}

void Alarm::on_pushButton_2_clicked()
{
    QString path = "/home/mose/Team/alarm/";

    QFile::remove(path + delete_file);
    QDir path_dir("/home/mose/Team/alarm/");
    QStringList files = path_dir.entryList(QDir::Files);
    ui->comboBox_3->clear();
    ui->comboBox_3->addItems(files);
    ui->comboBox_3->show();
}
