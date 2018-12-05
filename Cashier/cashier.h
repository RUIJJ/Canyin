#ifndef CASHIER_H
#define CASHIER_H

#include <QWidget>

namespace Ui {
class Cashier;
}

class Cashier : public QWidget
{
    Q_OBJECT

public:
    explicit Cashier(QWidget *parent = 0);
    ~Cashier();

private slots:
    void on_tw_menu_cellClicked(int row, int column);

    void on_tw_order_cellClicked(int row, int column);

    void on_pb_ok_clicked();

    void on_pb_re_clicked();

    void on_le_id_textEdited(const QString &arg1);

private:
    Ui::Cashier *ui;
    void initTwmenu(void);
    void initTworder(void);
    void initLeid(void);
};

#endif // CASHIER_H
