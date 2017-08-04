#ifndef CHECKINWIDGET_H
#define CHECKINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>
#include "checkinhistory.h"

class checkOutWidget : public QWidget
{
    Q_OBJECT
public:
    explicit checkOutWidget(checkInHistory*, int id);
    void setData(bool);

private slots:
    void toggleCheckOut();

private:
    QLabel *checkOut;
    QVBoxLayout *myQVBox;
    bool isCheckedOut;
    checkInHistory *mTimeLine;
    int BikeId;
};

#endif // CHECKINWIDGET_H
