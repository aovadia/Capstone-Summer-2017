#include "bikewindow.h"
#include "accountmanage.h"
#include "mytimer.h"
#include "rentaltimewidget.h"
#include "checkoutwidget.h"
#include "bikehealth.h"
#include "bikeserviced.h"
#include "checkinhistory.h"
#include <QDebug>
#include <QMessageBox>
#include <QSpacerItem>
#include <QTime>


bikeWindow::bikeWindow(QWidget *parent) : QWidget(parent)
{
    setupBikeWindow();
}

void bikeWindow::setupBikeWindow() {
    myQHBox = new QHBoxLayout(this);
    myQVBox = new QVBoxLayout();
    this->resize(400,400);

    enterBikeID = new QLabel();
    enterBikeID->setText("Enter Bike ID");
    enterBikeID->setAlignment(Qt::AlignCenter);


    myQVBox->addWidget(enterBikeID);

    editBikeID = new QLineEdit();
    editBikeID->setAlignment(Qt::AlignCenter);

    myQVBox->addWidget(editBikeID);
    acceptBikeID = new QPushButton();
    acceptBikeID->setText("Enter");

    myQVBox->addWidget(acceptBikeID);
    myQHBox->addLayout(myQVBox);

    this->setLayout(myQHBox);

    //When 'Enter' button is pressed, run 'checkBikeID'
    connect(acceptBikeID, &QPushButton::released, this, &bikeWindow::checkBikeID);

}

void bikeWindow::checkBikeID() {
    qDebug() <<"You pressed the accept button!";
    bool isValidInput;
    bikeID = editBikeID->text().toUInt(&isValidInput, 10);
    qDebug() <<"Bike ID: " <<bikeID;
    if (!isValidInput) {
        QMessageBox::warning(this, "Error", "Invalid Character!");
    } else {
        // Check sql server for matching bike id

        displayBikeInfo();
    }
}

void bikeWindow::displayBikeInfo() {
    this->resize(1500,1000);
    // Delete objects from window
    delete editBikeID;
    delete acceptBikeID;
    delete enterBikeID;

    QLabel *id = new QLabel("Bike ID: " +QString::number(bikeID));
    id->setFont(QFont("Times", 16, QFont::Bold));
    id->setAlignment(Qt::AlignHCenter);
    id->setStyleSheet("border:5px solid #000000");
    myQVBox->addWidget(id);

    QLabel *timeOfLastUpdate = new QLabel("Last Update: "+ setTimeOfUpdate());
    timeOfLastUpdate->setAlignment(Qt::AlignTop);
    myQVBox->addWidget(timeOfLastUpdate);

    checkInHistory *myCheckInHistory = new checkInHistory(bikeID);
    myQVBox->addWidget(myCheckInHistory);

    QSpacerItem *vertSpace = new QSpacerItem(200,2, QSizePolicy::Expanding, QSizePolicy::Expanding);
   // myQVBox->addSpacerItem(vertSpace);

    QVBoxLayout *QVBHealth = new QVBoxLayout();
    myQHBox->addLayout(QVBHealth);

    checkOutWidget *myCheckOut = new checkOutWidget();
    myQVBox->addWidget(myCheckOut);

    bikeHealth *myBikeHealth = new bikeHealth();
    QVBHealth->addWidget(myBikeHealth);

    bikeServiced *myBikeSeviced = new bikeServiced(myBikeHealth);
    myQVBox->addWidget(myBikeSeviced);

    rentalTimeWidget *myRentalTime = new rentalTimeWidget();
    QVBHealth->addWidget(myRentalTime);

    myTimer *myTimerLayout = new myTimer();
    QVBHealth->addWidget(myTimerLayout);

}

void bikeWindow::backToManagePage() {
    hide();
    accountManage *mManage = new accountManage();
    mManage->show();
}

QString bikeWindow::setTimeOfUpdate() {
    // Search database for time of last update
    return QString(QTime::currentTime().toString("hh:mm:ss")); //test
}
