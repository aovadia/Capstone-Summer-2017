#ifndef CHECKINHISTORY_H
#define CHECKINHISTORY_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
#include <QtSql/QSqlQuery>
#include <string>
#include <QDialog>
#include <QComboBox>
#include "rentaltimewidget.h"
class checkInHistory : public QWidget
{
    Q_OBJECT
public:
    explicit checkInHistory(const int id, rentalTimeWidget *a);
    void testEnterCheckinData();
    void setData(QVector<std::string>);
    bool setToggled(QDateTime, bool, int);
    void sendQuery(QSqlQuery *);

private slots:
    void copyCheckInData();
    void saveRentalTime();

private:
    int bikeID;
    int RentalPlan;
    QVBoxLayout *myQVBox;
    QListWidget *myList;
    QSqlQuery *query;
    void setRentalTime();
    QDialog *mDialog;
    QComboBox *mComboBox;
    void updateList(int BikeId);
    rentalTimeWidget *mTimeWidget;
};

#endif // CHECKINHISTORY_H
