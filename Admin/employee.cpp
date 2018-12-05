#include "employee.h"
#include "ui_employee.h"
#include "sqlconnect.h"
#include <QString>
#include <Qtsql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QString>
#include <QDate>
#include <QListWidgetItem>
#include <QMessageBox>

Employee::Employee(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Employee)
{
    ui->setupUi(this);

    QRegExp rx("^[0-9]*[1-9][0-9]*$");
    ui->le_1->setValidator(new QRegExpValidator(rx, this));
}

Employee::~Employee()
{
    delete ui;
}
void Employee::employeeChange(QStringList le)
{
    if(le.at(0)=="添加")
    {
        ui->pb_rm->hide();
        ui->lb_mode->setText("添加");
    }else
    {
        ui->pb_rm->show();
        ui->lb_mode->setText("修改");
        ui->le_1->setFocusPolicy(Qt::NoFocus);
        ui->le_1->setText(le.at(0));
        ui->le_2->setText(le.at(1));
    }
}

void Employee::on_pb_change_clicked()
{
    QStringList le;
    QSqlQuery query;
    QString wtosql;

    le << ui->le_1->text() << ui->le_2->text() << ui->cb->currentText();
    if(ui->lb_mode->text() == "添加")
    {
        wtosql = QString("select * from user where employee_id=%1").arg(le.at(0));
        query.exec(wtosql);
        query.next();
        if(query.value(0).toString() != "")
        {
            QMessageBox::critical(NULL, "操作错误","该职工已存在", QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    }else
    {
        wtosql = QString("delete from user where employee_id=%1").arg(le.at(0));
        query.exec(wtosql);
    }

    wtosql = QString("INSERT INTO user VALUES('%1','%2','%3')").arg(le.at(0)).arg(le.at(1)).arg(le.at(2));
    query.exec(wtosql);

    this->close();
}

void Employee::on_pb_rm_clicked()
{
    QSqlQuery query;
    QString wtosql;

    wtosql = QString("delete from user where employee_id=%1").arg(ui->le_1->text());
    query.exec(wtosql);

    this->close();
}
