#include "calendar.h"
#include "ui_calendar.h"

Calendar::Calendar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calendar)
{
    ui->setupUi(this);

    ui->textEdit->setReadOnly(edit);

    this->setWindowTitle("Calendar");

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(153, 153, 153, 255));
    setAutoFillBackground(true);
    setPalette(palette);
}

Calendar::~Calendar()
{
    delete ui;
}

void Calendar::dateColor(QList<QString> a, QList<QString> b)
{
   subject = a;
   due = b;
   check = 1;

   QTextCharFormat fmt;
   QDate date;
   fmt.setBackground(Qt::yellow);

   QList<QString>::iterator i;
   QString::iterator it;
   QChar j;

   int year;
   int month;
   int day;
   int total = 0;
   int exp = 7;
   int temp;

   for(i = due.begin(); i != due.end(); i++)
   {
       for(it = i->begin(); it != i->end(); it++)
       {
            if(*it != '-')
            {
                j = *it;
                temp = j.digitValue();

                for(int k = 0; k < exp; k++)
                  {
                    temp = temp * 10;
                  }

                 total = total + temp;

                 if(exp == 0)
                 {
                    exp = 8;
                 }

                 exp--;
            }
       }
       year = total / 10000;
       total = total % 10000;
       month = total / 100;
       total = total % 100;
       day = total;
       total = 0;
       date.setDate(year, month, day);
       ui->calendarWidget->setDateTextFormat(date, fmt);
   }

}

void Calendar::on_calendarWidget_clicked(const QDate &date)
{
    date.getDate(a,a+1,a+2);

    QList<int> temp;
    QList<int>::iterator it;
    int ch = 0;
    int ex = 0;

    title = QString::number(*a);
    if(*(a+1)<10){
            title=title+'0';
    }
    title=title+QString::number(*(a+1));
    if(*(a+2)<10){
        title=title+'0';
    }
    title=title+QString::number(*(a+2));
    QString fileName = path + title;

    for(int i = 0; i < due.length(); i++)
    {
        due[i].replace("-","");

        if(title == due[i])
        {
            temp.append(i);
            ex = 1;
        }

    }

    QFile file(fileName);

    if(file.exists() && !fileName.isEmpty() && check == 0){

        if(file.open(QFile::ReadOnly | QFile::Text)){
            QTextStream in(&file);
            QString text = in.readAll();
            file.close();

            ui->textEdit->setPlainText(text);
            ui->textEdit->setReadOnly(true);
        }
    }
    else if(check == 1 && ex == 1){
        for(it = temp.begin(); it != temp.end(); it++){
            if(ch == 0){
            ui->textEdit->setPlainText(subject[*it]);
            ch++;
            }
            else if(ch > 0){
                ui->textEdit->append(subject[*it]);
            }
        }
    }
    else if(!file.exists() && ex == 0){
        ui->textEdit->clear();
    }
}

void Calendar::dateColor()
{
   QTextCharFormat fmt;
   QDate date;
   fmt.setBackground(Qt::green);


   QDir path_dir("/home/mose/Team/calendar/");
   QStringList files = path_dir.entryList(QDir::Files);

   QList<QString>::iterator i;
   QString::iterator it;
   QChar j;

   int year;
   int month;
   int day;
   int total = 0;
   int exp = 7;
   int temp;

   for(i = files.begin(); i != files.end(); i++){
       for(it = i->begin(); it != i->end(); it++){
             j = *it;
             temp = j.digitValue();
             for(int k = 0; k < exp; k++){
                 temp = temp * 10;
           }
             total = total + temp;
             if(exp == 0){
                 exp = 8;
             }
             exp--;
       }
       year = total / 10000;
       total = total % 10000;
       month = total / 100;
       total = total % 100;
       day = total;
       total = 0;
       date.setDate(year, month, day);
       ui->calendarWidget->setDateTextFormat(date, fmt);
   }

}

void Calendar::dateColor(QString a, int b)
{
    QDate date;
    QTextCharFormat fmt;
    int year;
    int month;
    int day;

    if(b == 0)
    {
        fmt.setBackground(Qt::white);
    }
    else if( b == 1)
    {
        fmt.setBackground(Qt::green);
    }
    year = a.toInt() / 10000;
    month = (a.toInt() % 10000) / 100;
    day = a.toInt() % 100;

    date.setDate(year, month, day);
    ui->calendarWidget->setDateTextFormat(date, fmt);
}

void Calendar::on_pushButton_2_clicked()    //edit button
{
    if(check != 1)
    {
        edit = false;
        ui->textEdit->setReadOnly(edit);
    }
}

void Calendar::on_pushButton_3_clicked()           //save button
{
    if(check != 1)
    {
        save = 1;
        CalDate = ui->calendarWidget->selectedDate();
        CalDate.getDate(a,a+1,a+2);

        QFile sFile(path + title);

        if(sFile.open(QFile::WriteOnly | QFile::Text)){
            QTextStream out(&sFile);

            out << ui->textEdit->toPlainText();

            sFile.flush();
            sFile.close();
        }

        Calendar::dateColor(title, save);
        edit = true;
        ui->textEdit->setReadOnly(edit);
    }
}

void Calendar::on_pushButton_clicked()  //delete button
{
    if(check != 1)
    {
        save = 0;
        QFile::remove(path + title);
        ui->textEdit->clear();

        Calendar::dateColor(title, save);
        ui->calendarWidget->show();
    }
}
