#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <QWidget>

class analogClock: public QWidget
{
    Q_OBJECT
public:
    analogClock(QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent *event) override;
};

#endif // ANALOGCLOCK_H
