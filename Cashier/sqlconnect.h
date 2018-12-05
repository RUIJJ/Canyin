#ifndef SQLCONNECT_H
#define SQLCONNECT_H
#include <QString>

class sqlconnect
{
public:
    sqlconnect();
    void Connect();
    static QStringList getOfid(int);
    static QStringList getOfnum(int);
    static QStringList getMenuid();
    static QStringList getMenuname();
    static QStringList getMenuprice();
    static QString getPassword(QString);
    static QString getPower(QString);
    static QStringList getEmployeeid();
    static QStringList getEmployeename();
    static QStringList getEmployeepower();
};

#endif // SQLCONNECT_H
