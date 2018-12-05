#include "login.h"
#include "ui_login.h"
#include "sqlconnect.h"
#include <Qtsql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QString>
#include <QDate>
#include <QKeyEvent>
#include <QListWidgetItem>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pb_log_clicked()
{
    QString id,pw,power,wtosql,date;
    QSqlQuery query,fname;
    QDateTime date_time;

    id = ui->le_id->text();

    pw = sqlconnect::getPassword(id);
    if(QString::compare(pw,"") == 0)
    {
        ui->lb_show->setText(QString("No user"));
        ui->le_id->clear();
        ui->le_pw->clear();
        return;
    }else
    {
        if(QString::compare(pw,ui->le_pw->text()) == 0)
        {
            power = sqlconnect::getPower(id);
            if(QString::compare(power,"Admin") == 0)
            {
                this->close();
                Admin *admin = new Admin;
                admin->show();
            }else if(QString::compare(power,"Collect") == 0)
            {
                this->close();
                Cashier *cashier = new Cashier;
                cashier->show();
            }else
            {
                ui->lb_show->setText(QString("no power"));
                ui->le_id->clear();
                ui->le_pw->clear();
                return;
            }
        }else
        {
            ui->lb_show->setText(QString("Worng password"));
            ui->le_id->clear();
            ui->le_pw->clear();
            return;
        }
    }
    wtosql = QString("select employee_name from employee where employee_id = %1").arg(ui->le_id->text());
    fname.exec(wtosql);
    fname.next();
    date_time = QDateTime::currentDateTime();
    date = date_time.toString("yyyy-MM-dd hh:mm:ss ddd");
    wtosql = QString("INSERT INTO sign VALUES('%1','%2','%3')").arg(ui->le_id->text()).arg(fname.value(0).toString()).arg(date);
    query.exec(wtosql);
}

void Login::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == 16777220)
    {
        on_pb_log_clicked();
        return;
    }
    QWidget::keyReleaseEvent(ev);
}
