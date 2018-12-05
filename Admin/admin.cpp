#include "admin.h"
#include "ui_admin.h"
#include "change.h"
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

Admin::Admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);


    setWindowTitle("管理界面");
    initTwmenu();
    initTwemployee();
    initTwsign();
    initTwsheet();
    ui->le_search->setPlaceholderText("Search....");
    ui->le_search_2->setPlaceholderText("Search....");
    ui->le_date->setPlaceholderText("yyyy-MM-dd");
}

Admin::~Admin()
{
    delete ui;
}
//菜单
void Admin::initTwmenu(void)
{
     int i = 0;
     QStringList menu_id,menu_name,menu_price,header;

     menu_name = sqlconnect::getMenuname();
     menu_price = sqlconnect::getMenuprice();
     menu_id = sqlconnect::getMenuid();

     ui->tw_menu->setRowCount(0);
     ui->tw_menu->setColumnCount(3);

     header<<"菜号"<<"菜名"<<"单价";
     ui->tw_menu->setHorizontalHeaderLabels(header);

     for(i = 0;i < menu_name.size();i++)
     {
         ui->tw_menu->insertRow(i);
         ui->tw_menu->setItem(i,0,new QTableWidgetItem(menu_id.at(i)));
         ui->tw_menu->setItem(i,1,new QTableWidgetItem(menu_name.at(i)));
         ui->tw_menu->setItem(i,2,new QTableWidgetItem(menu_price.at(i)));
     }

     ui->tw_menu->setEditTriggers(QAbstractItemView::NoEditTriggers);
     ui->tw_menu->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui->tw_menu->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->tw_menu->sortByColumn(0,Qt::AscendingOrder);
}

void Admin::on_le_search_textEdited(const QString &arg1)
{
    int rowcount = ui->tw_menu->rowCount();
    int columncount = ui->tw_menu->columnCount();
    int row,colum;
    QString data;

    if(arg1.isEmpty())
    {
        for(int i = 0;i < rowcount;i++)
        {
            ui->tw_menu->showRow(i);
        }
        return;
    }

    for(row = 0;row < rowcount;row++)
    {
        for(colum = 0;colum < columncount;colum++)
        {
            if(ui->tw_menu->item(row,colum))
            {
                data += ui->tw_menu->item(row,colum)->text();
            }
        }

        if(!data.isEmpty())
        {
            if(data.contains(arg1))
            {
                ui->tw_menu->showRow(row);
            }else
            {
                ui->tw_menu->hideRow(row);
            }

        }else
        {
            ui->tw_menu->hideRow(row);
        }
        data.clear();
    }
}

void Admin::on_tw_menu_cellDoubleClicked(int row, int column)
{
    Change *change = new Change;
    change->show();
    QStringList le;
    int i;

    for(i = 0;i < ui->tw_menu->columnCount();i++)
    {
        le.append(ui->tw_menu->item(row,i)->text());
    }

    change->menuChange(le);
}

void Admin::on_pb_re_clicked()
{
    int i;
    for(i = 0;i < ui->tw_menu->rowCount();i++)
    {
        ui->tw_menu->removeRow(0);
    }

    initTwmenu();
}

void Admin::on_pb_add_clicked()
{
    Change *change = new Change;
    QStringList lb,le;
    int i;

    for(i = 0;i < ui->tw_menu->columnCount();i++)
    {
        lb.append(ui->tw_menu->horizontalHeaderItem(i)->text());
    }
    le.append("添加" );

    change->show();
    change->menuChange(le);

}
//职工
void Admin::initTwemployee(void)
{
     int i = 0;
     QStringList employee_id,employee_name,employee_power,header;

     employee_name = sqlconnect::getEmployeename();
     employee_power = sqlconnect::getEmployeepower();
     employee_id = sqlconnect::getEmployeeid();

     ui->tw_employee->setRowCount(0);
     ui->tw_employee->setColumnCount(3);

     header<<"工号"<<"密码"<<"职位";
     ui->tw_employee->setHorizontalHeaderLabels(header);

     for(i = 0;i < employee_name.size();i++)
     {
         ui->tw_employee->insertRow(i);
         ui->tw_employee->setItem(i,0,new QTableWidgetItem(employee_id.at(i)));
         ui->tw_employee->setItem(i,1,new QTableWidgetItem(employee_name.at(i)));
         ui->tw_employee->setItem(i,2,new QTableWidgetItem(employee_power.at(i)));
     }

     ui->tw_employee->setEditTriggers(QAbstractItemView::NoEditTriggers);
     ui->tw_employee->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui->tw_employee->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->tw_employee->sortByColumn(0,Qt::AscendingOrder);
}

void Admin::on_le_search_2_textEdited(const QString &arg1)
{
    int rowcount = ui->tw_employee->rowCount();
    int columncount = ui->tw_employee->columnCount();
    int row,colum;
    QString data;

    if(arg1.isEmpty())
    {
        for(int i = 0;i < rowcount;i++)
        {
            ui->tw_employee->showRow(i);
        }
        return;
    }

    for(row = 0;row < rowcount;row++)
    {
        for(colum = 0;colum < columncount;colum++)
        {
            if(ui->tw_employee->item(row,colum))
            {
                data += ui->tw_employee->item(row,colum)->text();
            }
        }

        if(!data.isEmpty())
        {
            if(data.contains(arg1))
            {
                ui->tw_employee->showRow(row);
            }else
            {
                ui->tw_employee->hideRow(row);
            }

        }else
        {
            ui->tw_employee->hideRow(row);
        }
        data.clear();
    }

}

void Admin::on_tw_employee_cellDoubleClicked(int row, int column)
{
    Employee *employee = new Employee;
    employee->show();
    QStringList lb,le;
    int i;

    for(i = 0;i < ui->tw_employee->columnCount();i++)
    {
        lb.append(ui->tw_employee->horizontalHeaderItem(i)->text());
        le.append(ui->tw_employee->item(row,i)->text());
    }

    employee->employeeChange(le);
}

void Admin::on_pb_add_2_clicked()
{
    Employee *employee = new Employee;
    QStringList lb,le;
    int i;

    for(i = 0;i < ui->tw_employee->columnCount();i++)
    {
        lb.append(ui->tw_employee->horizontalHeaderItem(i)->text());
    }
    le.append("添加");

    employee->show();
    employee->employeeChange(le);
}

void Admin::on_pb_re_2_clicked()
{
    int i;
    for(i = 0;i < ui->tw_employee->rowCount();i++)
    {
        ui->tw_employee->removeRow(0);
    }

    initTwemployee();

}

void Admin::initTwsign(void)
{
     QSqlQuery query;
     QStringList header;

     ui->tw_sign->setRowCount(0);
     ui->tw_sign->setColumnCount(3);

     header<<"工号"<<"姓名"<<"签到时间";
     ui->tw_sign->setHorizontalHeaderLabels(header);

     query.exec(QString("select * from sign"));

     while(query.next())
     {
         ui->tw_sign->insertRow(0);
         ui->tw_sign->setItem(0,0,new QTableWidgetItem(query.value(0).toString()));
         ui->tw_sign->setItem(0,1,new QTableWidgetItem(query.value(1).toString()));
         ui->tw_sign->setItem(0,2,new QTableWidgetItem(query.value(2).toString()));
     }

     ui->tw_sign->setEditTriggers(QAbstractItemView::NoEditTriggers);
     ui->tw_sign->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui->tw_sign->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->tw_sign->sortByColumn(3,Qt::AscendingOrder);
}

void Admin::initTwsheet()
{
     int i = 0;
     QSqlQuery query,order;
     QString num,total,wtosql,ndate;
     QStringList menu_name,header;

     QString date;
     date = QDateTime::currentDateTime().toString("yyyy-MM-dd");

     menu_name = sqlconnect::getMenuname();

     ui->tw_sheet->setRowCount(0);
     ui->tw_sheet->setColumnCount(3);

     header<<"菜号"<<"菜名"<<"销量";
     ui->tw_sheet->setHorizontalHeaderLabels(header);

     wtosql = QString("delete from sheet where today = '%1'").arg(date);
     query.exec(wtosql);

     ui->tw_sheet->setRowCount(0);
     for(i = 0;i < menu_name.size();i++)
     {
         num = QString::number(i+1);
         total = QString("select SUM(food_num) from m_order where (food_id = %1) and (today = '%2')").arg(i+1).arg(date);
         order.exec(total);
         order.next();

         ui->tw_sheet->insertRow(i);
         ui->tw_sheet->setItem(i,0,new QTableWidgetItem(num));
         ui->tw_sheet->setItem(i,1,new QTableWidgetItem(menu_name.at(i)));
         ui->tw_sheet->setItem(i,2,new QTableWidgetItem(order.value(0).toString()));

         wtosql = QString("INSERT INTO sheet VALUES('%1','%2','%3')").arg(i+1).arg(order.value(0).toInt()).arg(date);
         query.exec(wtosql);

     }

     ui->tw_sheet->setEditTriggers(QAbstractItemView::NoEditTriggers);
     ui->tw_sheet->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui->tw_sheet->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void Admin::on_pb_datesearch_clicked()
{
    QSqlQuery query;
    QString date;
    int i;

    date =QString("select * from sheet where today = '%1'").arg(ui->le_date->text());
    query.exec(date);
    query.next();

    if(QString::compare(query.value(0).toString(),QString("")) == 0)
    {
        QMessageBox::critical(NULL, "错误", "请按'yyyy-MM-dd'输入日期", QMessageBox::Yes, QMessageBox::Yes);
    }else
    {
        for(i = 0;i < ui->tw_sheet->rowCount();i++)
        {
            ui->tw_sheet->setItem(i,2,new QTableWidgetItem(query.value(1).toString()));
            query.next();
        }
    }
}
