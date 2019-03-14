#include "memo.h"
#include "ui_memo.h"
#include <QLabel>
#include <QFileDialog>
#include <QFile>
#include <QtWidgets>
#include <QMenuBar>
#include <QPixmap>


Memo::Memo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Memo)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    this->setWindowTitle("Text Editor");
}

Memo::~Memo()
{
    delete ui;
}

void Memo::on_actionNew_triggered()
{
    mFilename = "";
    ui->textEdit->setPlainText("");
}

void Memo::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, "Open a file");

        if(!file.isEmpty()){
            QFile sFile(file);
            if(sFile.open(QFile::ReadOnly | QFile::Text)){
                mFilename = file;
                QTextStream in(&sFile);
                QString text = in.readAll();
                sFile.close();

                ui->textEdit->setPlainText(text);
            }
        }
}

void Memo::on_actionSave_triggered()
{
    QFile sFile(mFilename);
        if(sFile.open(QFile::WriteOnly | QFile::Text)){
            QTextStream out(&sFile);

            out << ui->textEdit->toPlainText();

            sFile.flush();
            sFile.close();
        }
}

void Memo::on_actionSave_AS_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, "Open a file");

        if(!file.isEmpty()){
            mFilename = file;
            on_actionSave_triggered();
        }
}

void Memo::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void Memo::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void Memo::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void Memo::on_actionUndo_2_triggered()
{
    ui->textEdit->undo();
}

void Memo::on_actionRedo_2_triggered()
{
    ui->textEdit->redo();
}

void Memo::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About Application"), tr("write modern GUI application using Qt, with a menu bar"));
}
