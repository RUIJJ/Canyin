#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include "change.h"
#include "employee.h"

namespace Ui {
class Admin;
}

class Admin : public QWidget
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = 0);
    ~Admin();
    void initTwmenu(void);
    void initTwemployee(void);
    void initTwsign(void);
    void initTwsheet();
    void meschange(QStringList, QStringList);


private slots:

    void on_le_search_textEdited(const QString &arg1);

    void on_tw_menu_cellDoubleClicked(int row, int column);

    void on_pb_re_clicked();

    void on_pb_add_clicked();

    void on_le_search_2_textEdited(const QString &arg1);

    void on_tw_employee_cellDoubleClicked(int row, int column);

    void on_pb_add_2_clicked();

    void on_pb_re_2_clicked();

    void on_pb_datesearch_clicked();

private:
    Ui::Admin *ui;
    //Change change;
    //Employee employee;
};

#endif // ADMIN_H
