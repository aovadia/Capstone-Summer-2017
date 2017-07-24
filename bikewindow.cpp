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
    std::string statement = "SELECT BikeId FROM Master WHERE BikeId = ";
    std::string val = std::to_string(bikeID);
    statement.append(val);
    if (query.exec(QString::fromUtf8(statement.c_str()))) {
        if (query.next()) displayBikeInfo(bikeID);
        else QMessageBox::critical(this, "Error", "Not a valid bike.\nPlease try again.");
    }
    else QMessageBox::warning(this, "Connection error", "try again in a few seconds");
}

void bikeWindow::displayBikeInfo(int bid) {
    bool CheckedOut, Service;
    double Distance;
    int Health, rentalTime;
    QVector<std::string> timeline;
    std::string statement = "SELECT * FROM Master WHERE BikeId = ";
    std::string val = std::to_string(bid);
    statement.append(val);
    bool receivedMaster;
    if (query.exec(QString::fromUtf8(statement.c_str()))) {
        receivedMaster = true;
        query.next();
        CheckedOut = query.value(1).toBool();
        Service = query.value(2).toBool();
        Distance = query.value(3).toDouble();
        Health = query.value(4).toInt();
    }
    else QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    bool firstTimeDone;
    statement = "SELECT * FROM Rentals WHERE BikeId = ";
    statement.append(val);
    statement.append(" ORDER BY RentalId DESC");
    bool receivedRental;
    int latestRentalId;
    if (query.exec(QString::fromUtf8(statement.c_str()))) {
        receivedRental = true;
        while (query.next()) {
            if (!firstTimeDone) {
                latestRentalId = query.value(0).toInt();
                firstTimeDone = true;
                rentalTime = query.value(4).toInt();
            }
            if (query.value(3).toString() != NULL) {
                timeline.push_back(query.value(3).toString().toStdString().append("I")); //apend I
            }
            timeline.push_back(query.value(2).toString().toStdString());
        }
    }
    else QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    qDebug() <<"checkout: " <<CheckedOut <<"service: " <<Service <<"Distance: " <<Distance <<"Health: " <<Health;

    qDebug() <<"rental id: " <<latestRentalId << "rental time: " <<rentalTime;

    for (int a = 0; a < timeline.size(); a++) {
        for (int b = 0; b < timeline[a].size(); b++) {
            if (timeline[a][b] == 'T') timeline[a][b] = ' ';
        }
        qDebug() <<"timeline: " <<QString::fromUtf8(timeline[a].c_str());
    }
    this->resize(1500,1000);
    // Delete objects from window
    delete editBikeID;
    delete acceptBikeID;
    delete enterBikeID;
    QLabel *id = new QLabel("Bike ID: " +QString::number(bid));
    id->setFont(QFont("Times", 16, QFont::Bold));
    id->setAlignment(Qt::AlignHCenter);
    id->setStyleSheet("border:5px solid #000000");
    myQVBox->addWidget(id);

    QVBoxLayout *QVBHealth = new QVBoxLayout();
    myQHBox->addLayout(QVBHealth);

    QLabel *timeOfLastUpdate = new QLabel("Last Update: "+ setTimeOfUpdate());
    timeOfLastUpdate->setAlignment(Qt::AlignTop);
    myQVBox->addWidget(timeOfLastUpdate);

    bikeHealth *myBikeHealth = new bikeHealth(bikeID);
    myBikeHealth->sendQuery(query);
    myBikeHealth->setData(Health);
    QVBHealth->addWidget(myBikeHealth);

    rentalTimeWidget *myRentalTime = new rentalTimeWidget();
    myRentalTime->setData(rentalTime);
    QVBHealth->addWidget(myRentalTime);

    checkInHistory *myCheckInHistory = new checkInHistory(bikeID, myRentalTime);
    myCheckInHistory->setData(timeline);
    myCheckInHistory->sendQuery(query);
    myQVBox->addWidget(myCheckInHistory);

   // myQVBox->addSpacerItem(vertSpace);



    checkOutWidget *myCheckOut = new checkOutWidget(myCheckInHistory);
    myCheckOut->setData(CheckedOut);
    myQVBox->addWidget(myCheckOut);



    bikeServiced *myBikeSeviced = new bikeServiced(myBikeHealth);
    myBikeSeviced->accessSql(query, bikeID);
    myBikeSeviced->setData(Service);
    myQVBox->addWidget(myBikeSeviced);

    myTimer *myTimerLayout = new myTimer();
    myTimerLayout->setData(0);
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

void bikeWindow::queryAccess(QSqlQuery a) {
    query = a;
}
