#ifndef CHECKINWIDGET_H
#define CHECKINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>

class checkOutWidget : public QWidget
{
    Q_OBJECT
public:
    explicit checkOutWidget();

private slots:
    void toggleCheckOut();

private:
    QLabel *checkOut;
    QVBoxLayout *myQVBox;
    bool isCheckedOut;
    QString getCheckOutData();
};

#endif // CHECKINWIDGET_H
