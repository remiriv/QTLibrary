#ifndef DIALOG_H
#define DIALOG_H

#include <QInputDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QInputDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void setState(QString);
    QString getState();

private:
    Ui::Dialog *ui;
    QString state;

private slots:
};

#endif // DIALOG_H
