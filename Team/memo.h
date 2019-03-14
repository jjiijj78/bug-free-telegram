#ifndef MEMO_H
#define MEMO_H

#include <QMainWindow>
#include <QPixmap>

namespace Ui {
class Memo;
}

class Memo : public QMainWindow
{
    Q_OBJECT

public:
    explicit Memo(QWidget *parent = nullptr);
    ~Memo();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_AS_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_2_triggered();

    void on_actionRedo_2_triggered();

    void on_actionAbout_triggered();

private:
    Ui::Memo *ui;
    QString mFilename;
};

#endif // MEMO_H
