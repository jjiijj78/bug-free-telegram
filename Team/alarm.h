#ifndef ALARM_H
#define ALARM_H

#include "alarm_widget.h"
#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QFile>
#include <QtWidgets>
#include <QMenuBar>
#include <QWidget>
#include <QDate>
#include <QList>

namespace Ui {
class Alarm;
}

class Alarm : public QWidget
{
    Q_OBJECT

public:
    explicit Alarm(QWidget *parent = nullptr);
    QList<int>* get_AlarmList(void);
    void check_Alarm(QTime time);
    ~Alarm();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_currentIndexChanged(int index);

    void on_spinBox_valueChanged(int arg1);


    void on_comboBox_3_currentIndexChanged(const QString &arg1);

    void on_pushButton_2_clicked();

private:
    Ui::Alarm *ui;
    QDate date;
    QList<int> v,temp;
    int a[6];
    alarm_widget *sound;
    QString delete_file;
};


#endif // ALARM_H
