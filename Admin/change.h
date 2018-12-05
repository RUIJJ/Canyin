#ifndef CHANGE_H
#define CHANGE_H

#include <QWidget>

namespace Ui {
class Change;
}

class Change : public QWidget
{
    Q_OBJECT

public:
    explicit Change(QWidget *parent = 0);
    ~Change();
    void menuChange(QStringList);

private slots:
    void on_pb_change_clicked();

    void on_pb_rm_clicked();

private:
    Ui::Change *ui;
};

#endif // CHANGE_H
