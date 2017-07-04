#ifndef ACCOUNTMANAGE_H
#define ACCOUNTMANAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include "bikewindow.h"

class accountManage : public QWidget
{

public:
    explicit accountManage(QWidget *parent = 0);
private:
    QVBoxLayout *myQVBox;
    QHBoxLayout *myQHBox4;
    bikeWindow *myBikeWindow;


    void addNewBike();
    void searchForBike();
    void displayStatistics();

    int cSearch;
};

#endif // ACCOUNTMANAGE_H
