#include "sqlconnect.h"
#include <Qtsql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QDate>

sqlconnect::sqlconnect()
{

}

void sqlconnect::Connect()
{
    QSqlDatabase db;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("canyin.db");
    if(!db.open()){
        qCritical("Can't open database: %s(%s)",
            db.lastError().text().toLocal8Bit().data(),
            qt_error_string().toLocal8Bit().data());
        qDebug() << "false";
    }else
    {
        qDebug() << "true";
    }
}

QStringList sqlconnect::getOfid(int order)
{
    QStringList list;
    QSqlQuery query;
    QString mes;
    QDateTime date_time = QDateTime::currentDateTime();
    QString date = date_time.toString("yyyy-MM-dd");

    mes = QString("select * from m_order where (order_id = %1) and (today = '%2') ").arg(order).arg(date);
    query.exec(mes);
    while(query.next())
    {
        list.append(query.value(1).toString());
    }
    return list;
}

QStringList sqlconnect::getOfnum(int order)
{
    QStringList list;
    QSqlQuery query;
    QString mes;
    QDateTime date_time = QDateTime::currentDateTime();
    QString date = date_time.toString("yyyy-MM-dd");

    mes = QString("select * from m_order where (order_id = %1) and (today = '%2')").arg(order).arg(date);
    query.exec(mes);
    while(query.next())
    {
        list.append(query.value(2).toString());
    }
    return list;
}

QStringList sqlconnect::getMenuid()
{
    QStringList list;
    QSqlQuery query;
    QString mes;

    mes = QString("select * from menu");
    query.exec(mes);
    while(query.next())
    {
        list.append(query.value(0).toString());
    }
    return list;
}

QStringList sqlconnect::getMenuname()
{
    QStringList list;
    QSqlQuery query;
    QString mes;

    mes = QString("select * from menu");
    query.exec(mes);
    while(query.next())
    {
        list.append(query.value(1).toString());
    }
    return list;
}

QStringList sqlconnect::getMenuprice()
{
    QStringList list;
    QSqlQuery query;
    QString mes;

    mes = QString("select * from menu");
    query.exec(mes);
    while(query.next())
    {
        list.append(query.value(2).toString());
    }
    return list;
}

QString sqlconnect::getPassword(QString id)
{
    QString password;
    QSqlQuery query;
    QString mes;

    mes = QString("select employee_pass from user where employee_id = %1").arg(id);
    query.exec(mes);
    query.next();
    password = query.value(0).toString();

    return password;
}

QString sqlconnect::getPower(QString id)
{
    QString power;
    QSqlQuery query;
    QString mes;

    mes = QString("select employee_power from user where employee_id = %1").arg(id);
    query.exec(mes);
    query.next();
    power = query.value(0).toString();

    return power;
}

QStringList sqlconnect::getEmployeeid()
{
    QStringList list;
    QSqlQuery query;
    QString mes;

    mes = QString("select * from user");
    query.exec(mes);
    while(query.next())
    {
        list.append(query.value(0).toString());
    }
    return list;
}

QStringList sqlconnect::getEmployeename()
{
    QStringList list;
    QSqlQuery query;
    QString mes;

    mes = QString("select * from user");
    query.exec(mes);
    while(query.next())
    {
        list.append(query.value(1).toString());
    }
    return list;
}

QStringList sqlconnect::getEmployeepower()
{
    QStringList list;
    QSqlQuery query;
    QString mes;

    mes = QString("select * from user");
    query.exec(mes);
    while(query.next())
    {
        list.append(query.value(2).toString());
    }
    return list;
}
