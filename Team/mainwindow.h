#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "weatherclass.h"
#include "alarm.h"

#include "memoclass.h"
#include "memo.h"
#include "calendar.h"
#include "cauclass.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void myfunction();
    void on_MemoButton_clicked();

    void on_AlarmButton_clicked();

    void on_WeatherButton_clicked();

    void on_CauButton_clicked();

    void on_CalendarButton_clicked();



    void on_ExitButton_clicked();

private:
    Ui::MainWindow *ui;
    Memo *memo;
    QTimer *timer;
    Alarm *alarm;
    QList<int> *temp;
    weatherclass *weather;

    QDate today;
    int day[3];
    Calendar *calendar;


    cauclass *cau;
};

#endif // MAINWINDOW_H
