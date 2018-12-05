#include "cashier.h"
#include "ui_cashier.h"
#include "sqlconnect.h"
#include <Qtsql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QString>
#include <QDate>
#include <QListWidgetItem>
#include <QMessageBox>

Cashier::Cashier(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cashier)
{
    ui->setupUi(this);

    initTwmenu();
    initTworder();
    initLeid();
}

Cashier::~Cashier()
{
    delete ui;
}

void Cashier::initTwmenu(void)
{
     int i = 0;
     QStringList menu_name,menu_price,header;
     QString num;

     menu_name = sqlconnect::getMenuname();

     menu_price = sqlconnect::getMenuprice();

     ui->tw_menu->setRowCount(0);
     ui->tw_menu->setColumnCount(3);

     header<<"菜号"<<"菜名"<<"单价";
     ui->tw_menu->setHorizontalHeaderLabels(header);

     for(i = 0;i < menu_name.size();i++) 
     {
         num = QString::number(i+1);
         ui->tw_menu->insertRow(i);
         ui->tw_menu->setItem(i,0,new QTableWidgetItem(num));
         ui->tw_menu->setItem(i,1,new QTableWidgetItem(menu_name.at(i)));
         ui->tw_menu->setItem(i,2,new QTableWidgetItem(menu_price.at(i)));
     }

     ui->tw_menu->setEditTriggers(QAbstractItemView::NoEditTriggers);
     ui->tw_menu->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui->tw_menu->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void Cashier::initLeid(void)
{
    QSqlQuery order;
    QString date,mes;

    date = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    mes = QString("select Max(order_id) order_id from m_order where today = '%1'").arg(date);

    order.exec(mes);
    order.next();

    ui->le_id->setText(QString::number(order.value(0).toInt() + 1));
}

void Cashier::initTworder(void)
{
    QStringList header;

    ui->tw_order->setRowCount(0);
    ui->tw_order->setColumnCount(4);

    header<<"菜号"<<"菜名"<<"单价"<<"数量";
    ui->tw_order->setHorizontalHeaderLabels(header);


    ui->tw_order->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_order->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_order->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void Cashier::on_tw_menu_cellClicked(int row, int column)
{
    int i,num;
    QString snum;
    QString mes;
    int list = ui->tw_order->rowCount();
    for(i = 0;i < list;i++)
    {
        if(ui->tw_order->item(i,0)->text() == ui->tw_menu->item(row,0)->text())
        {
            snum = ui->tw_order->item(i,3)->text();
            num = snum.toInt() + 1;
            snum = QString::number(num);
            ui->tw_order->item(i,3)->setText(snum);
            return;
        }
    }
    ui->tw_order->insertRow(0);
    for(i = 0;i < 3;i++)
    {
        mes = ui->tw_menu->item(row,i)->text();
        ui->tw_order->setItem(0,i,new QTableWidgetItem(mes));
    }
    snum = QString::number(1);
    ui->tw_order->setItem(0,3,new QTableWidgetItem(snum));
}

void Cashier::on_tw_order_cellClicked(int row, int column)
{
    QString snum = ui->tw_order->item(row,3)->text();
    int num = snum.toInt();
    if(num > 1)
    {
        snum = QString::number(num - 1);
        ui->tw_order->setItem(row,3,new QTableWidgetItem(snum));
    }else if(num == 1)
    {
        ui->tw_order->removeRow(row);
    }else
    {
        return;
    }
}

void Cashier::on_pb_ok_clicked()
{
    QDateTime date_time = QDateTime::currentDateTime();
    QString date = date_time.toString("yyyy-MM-dd");
    int listnum = ui->tw_order->rowCount();
    int total = 0;
    int i,order;
    QString wtosql,money,mes;
    QSqlQuery query,order_id;

    order = ui->le_id->text().toInt();
    if(listnum != 0)
    {
        wtosql = QString("delete from m_order where (order_id=%1) and (today = '%2')").arg(order).arg(date);
        query.exec(wtosql);
        for(i = 0;i < listnum;i++)
        {
            wtosql = QString("INSERT INTO m_order VALUES('%1','%2','%3','%4')").arg(order)
                    .arg(ui->tw_order->item(i,0)->text().toInt()).arg(ui->tw_order->item(i,3)->text().toInt())
                    .arg(date);
            query.exec(wtosql);
            total += (ui->tw_order->item(i,2)->text().toInt())*(ui->tw_order->item(i,3)->text().toInt());
        }
        mes = QString("select Max(order_id) order_id from m_order where today = '%1'").arg(date);
        order_id.exec(mes);
        order_id.next();
        ui->le_id->setText(QString::number(order_id.value(0).toInt() + 1));
        ui->tw_order->setRowCount(0);
        money = QString("请支付 %1 元").arg(total);
        QMessageBox::critical(NULL, "总金额", money, QMessageBox::Yes, QMessageBox::Yes);
    }else if(listnum == 0)
    {
        wtosql = QString("delete from m_order where order_id=%1").arg(order);
        query.exec(wtosql);
        mes = QString("select Max(order_id) order_id from m_order where today = '%1'").arg(date);
        order_id.exec(mes);
        order_id.next();
        ui->le_id->setText(QString::number(order_id.value(0).toInt() + 1));
    }
}

void Cashier::on_pb_re_clicked()
{
    QSqlQuery order_id;
    QDateTime date_time = QDateTime::currentDateTime();
    QString date = date_time.toString("yyyy-MM-dd");
    QString mes;

    mes = QString("select Max(order_id) order_id from m_order where today = '%1'").arg(date);
    order_id.exec(mes);
    order_id.next();
    ui->le_id->setText(QString::number(order_id.value(0).toInt() + 1));
    ui->tw_order->setRowCount(0);
}

void Cashier::on_le_id_textEdited(const QString &arg1)
{
    int order,id;
    int i = 0;
    QStringList idlist,numlist,menulist,pricelist;

    ui->tw_order->setRowCount(0);

    order = ui->le_id->text().toInt();

    idlist = sqlconnect::getOfid(order);
    numlist = sqlconnect::getOfnum(order);
    menulist = sqlconnect::getMenuname();
    pricelist = sqlconnect::getMenuprice();

    for(i = idlist.size();i > 0;i--)
    {
        ui->tw_order->insertRow(0);

        id = idlist.at(i-1).toInt();
        ui->tw_order->setItem(0,0,new QTableWidgetItem(idlist.at(i-1)));
        ui->tw_order->setItem(0,1,new QTableWidgetItem(menulist.at(id-1)));
        ui->tw_order->setItem(0,2,new QTableWidgetItem(pricelist.at(id-1)));
        ui->tw_order->setItem(0,3,new QTableWidgetItem(numlist.at(i-1)));
    }
}
