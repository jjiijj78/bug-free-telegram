#ifndef ALARM_WIDGET_H
#define ALARM_WIDGET_H

#include <QWidget>
#include <QMediaPlayer>

namespace Ui {
class alarm_widget;
}

class alarm_widget : public QWidget
{
    Q_OBJECT

public:
    explicit alarm_widget(QWidget *parent = nullptr);
    ~alarm_widget();

private slots:

    void on_pushButton_clicked();

private:
    Ui::alarm_widget *ui;
    QMediaPlayer *music;
};

#endif // ALARM_WIDGET_H
