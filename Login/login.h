#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QKeyEvent>
#include "cashier.h"
#include "admin.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
//    Cashier cashier;
//    Admin admin;

private slots:
    void on_pb_log_clicked();

private:
    Ui::Login *ui;
    virtual void keyPressEvent(QKeyEvent *ev);
};

#endif // LOGIN_H
