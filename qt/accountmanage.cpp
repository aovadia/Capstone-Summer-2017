#include "accountmanage.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QDebug>
#include <QMessageBox>

accountManage::accountManage(QWidget *parent) : QWidget(parent)
{
    cSearch = 0;
    myQVBox = new QVBoxLayout();
    this->resize(800,500);
    setWindowTitle("Account Management");

    QHBoxLayout *myQHBox = new QHBoxLayout();
    QHBoxLayout *myQHBox2 = new QHBoxLayout();
    QHBoxLayout *myQHBox3 = new QHBoxLayout();

    QSpacerItem *mySpacer = new QSpacerItem(400,2);



    QPushButton *newBike = new QPushButton();
    QPushButton *searchBike = new QPushButton();
    QPushButton *statBike = new QPushButton();

    newBike->setText("Add a new Bike");
    searchBike->setText("Search for a Bike");
    statBike->setText("Bike statistics");


   // myQHBox->addSpacerItem(mySpacer);
    myQHBox->addWidget(newBike);

   // myQHBox2->addSpacerItem(mySpacer);
    myQHBox2->addWidget(searchBike);

 //   myQHBox3->addSpacerItem(mySpacer);
    myQHBox3->addWidget(statBike);

    myQVBox->addLayout(myQHBox);
    myQVBox->addLayout(myQHBox2);
    myQVBox->addLayout(myQHBox3);

    myQHBox4 = new QHBoxLayout(this);
    myQHBox4->addLayout(myQVBox);

    setLayout(myQHBox4);

    connect(newBike, &QPushButton::released,this, &accountManage::addNewBike);
    connect(searchBike, &QPushButton::released, this, &accountManage::searchForBike);
    connect(statBike, &QPushButton::released, this, &accountManage::displayStatistics);

}

void accountManage::addNewBike() {

    // Create the elements neccessary for a new bike
    // Send data to the server


    QMessageBox::information(this, "Success", "New Bike successfully created!");

}

void accountManage::searchForBike() {
    // Search for a bike in database and show all associated data about bike
   // hide(); // hide current view
    //myBikeWindow->show();
    myQHBox4->removeItem(myQVBox);
    if (cSearch > 0) { /* Prevent window from opening multiple 'myBikeWindow' instances */
        myQHBox4->removeWidget(myBikeWindow);
        delete myBikeWindow;
        cSearch--;
    }
    myBikeWindow = new bikeWindow();
    myQHBox4->addWidget(myBikeWindow);
    myQHBox4->addLayout(myQVBox);
    cSearch++;

}

void accountManage::displayStatistics() {

}
