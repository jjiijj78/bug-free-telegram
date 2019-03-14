#ifndef CALENDAR_H
#define CALENDAR_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDate>

namespace Ui {
class Calendar;
}

class Calendar : public QWidget
{
    Q_OBJECT

public:
    explicit Calendar(QWidget *parent = nullptr);
    void dateColor();
    void dateColor(QString a, int b);
    void dateColor(QList<QString> a, QList<QString> b);
    ~Calendar();

private slots:
    void on_calendarWidget_clicked(const QDate &date);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Calendar *ui;
    int a[3];
    QString path = "/home/mose/Team/calendar/";
    QStringList subject;
    QStringList due;
    QString title;
    QDate CalDate;
    int check = 0;
    bool edit = true;
    int save = 0;
};

#endif // CALENDAR_H
