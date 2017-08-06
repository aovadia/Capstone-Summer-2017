#ifndef CHECKINWIDGET_H
#define CHECKINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>
#include <QtSql/QSqlQuery>
#include "checkinhistory.h"

class checkOutWidget : public QWidget
{
    Q_OBJECT
public:
    explicit checkOutWidget(checkInHistory*, int id);
    void setData(bool, QSqlQuery *);

private slots:
    void toggleCheckOut();

private:
    QLabel *checkOut;
    QVBoxLayout *myQVBox;
    bool isCheckedOut;
    checkInHistory *mTimeLine;
    int BikeId;
    QSqlQuery *query;
};

#endif // CHECKINWIDGET_H
