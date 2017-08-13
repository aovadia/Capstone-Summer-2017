#ifndef ACCOUNTMANAGE_H
#define ACCOUNTMANAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include "bikewindow.h"
#include "statistics.h"
#include <QtSql/QSqlQuery>
//Statistics *mStat;

class accountManage : public QWidget
{

public:
    explicit accountManage(QWidget *parent = 0);
    void queryAccess(QSqlQuery *a);
    QVBoxLayout *myQVBox;
    QHBoxLayout *myQHBox4;
    bikeWindow *myBikeWindow;
    bikeWindow *myBikeWindow2;
    bikeWindow *myBikeWindow3;
    QSqlQuery *query;
    void removeActiveWindows();
    bool isAddBikeActive;
    bool isBikeWindowActive;
    void accessBikeWindow(int);

private:
    Statistics *mStat;
    void addNewBike();
    void searchForBike();
    void displayStatistics();
    bool isStatisticsActice;
};

#endif // ACCOUNTMANAGE_H
