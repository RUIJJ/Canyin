#include "change.h"
#include "ui_change.h"
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

Change::Change(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Change)
{
    ui->setupUi(this);

    QRegExp rx("^[0-9]*[1-9][0-9]*$");
    ui->le_1->setValidator(new QRegExpValidator(rx, this));
    ui->le_3->setValidator(new QRegExpValidator(rx, this));
}

Change::~Change()
{
    delete ui;
}

void Change::menuChange(QStringList le)
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
        ui->le_3->setText(le.at(2));
    }
}

void Change::on_pb_change_clicked()
{
    QStringList le;
    QSqlQuery query;
    QString wtosql;

    le << ui->le_1->text() << ui->le_2->text() << ui->le_3->text();
    if(ui->lb_mode->text() == "添加")
    {
        wtosql = QString("select * from menu where 0food_id=%1").arg(le.at(0));
        query.exec(wtosql);
        query.next();
        if(query.value(0).toString() != "")
        {
            return;
        }
    }else
    {
        wtosql = QString("delete from menu where food_id=%1").arg(le.at(0));
        query.exec(wtosql);
    }

    wtosql = QString("INSERT INTO menu VALUES('%1','%2','%3')").arg(le.at(0)).arg(le.at(1)).arg(le.at(2));
    query.exec(wtosql);

    this->close();
}

void Change::on_pb_rm_clicked()
{
    QSqlQuery query;
    QString wtosql;

    wtosql = QString("delete from menu where food_id=%1").arg(ui->le_1->text());
    query.exec(wtosql);

    this->close();
}
