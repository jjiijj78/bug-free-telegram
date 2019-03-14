#include "alarm_widget.h"
#include "ui_alarm_widget.h"

#include <QUrl>
#include <iostream>

alarm_widget::alarm_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alarm_widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Alarm");
    music = new QMediaPlayer(this);
    music->setMedia(QUrl("qrc:/music/music2.mp3"));
    music->setVolume(50);
    music->play();
}

alarm_widget::~alarm_widget()
{
    delete ui;
    music->stop();
}


void alarm_widget::on_pushButton_clicked()
{
    music->stop();
    this->close();
}
