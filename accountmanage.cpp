#include <QPushButton>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QMessageBox>
#include "accountmanage.h"

accountManage::accountManage(QWidget *parent) : QWidget(parent)
{
    isBikeWindowActive = false;
    isAddBikeActive = false;
    isStatisticsActice = false;

    myQVBox = new QVBoxLayout();
    this->resize(800,500);
    setWindowTitle("Account Management");

    QHBoxLayout *myQHBox = new QHBoxLayout();
    QHBoxLayout *myQHBox2 = new QHBoxLayout();
    QHBoxLayout *myQHBox3 = new QHBoxLayout();


    QPushButton *newBike = new QPushButton();
    QPushButton *searchBike = new QPushButton();
    QPushButton *statBike = new QPushButton();

    newBike->setText("Add a new Bike");
    searchBike->setText("Search for a Bike");
    statBike->setText("Bike statistics");

    myQHBox->addWidget(newBike);

    myQHBox2->addWidget(searchBike);

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
   if (query->exec("SELECT COUNT(*) FROM Master")) {
        query->next();
        int total = query->value(0).toInt();
        total++;
        std::string queryEnd = std::to_string(total);
        std::string statement = "INSERT INTO Master (BikeId, CheckedOut, Service, Distance, Health) VALUES(";
        statement.append(queryEnd);
        statement.append(", 0, 0, 0, 10)");
        if (query->exec(QString::fromUtf8(statement.c_str()))) {
            QMessageBox::information(this, "Success", "New Bike successfully created!");
            myQHBox4->removeItem(myQVBox);
            removeActiveWindows();
            myBikeWindow2 = new bikeWindow();
            isAddBikeActive = true;
            myBikeWindow2->queryAccess(query);
            myBikeWindow2->displayBikeInfo(total);
            myQHBox4->addWidget(myBikeWindow2);
            myQHBox4->addLayout(myQVBox);
        }
        else {
            QMessageBox::critical(this, "Connection error", "try again in a few seconds");
        }
    }
    else {
       QMessageBox::information(this, "Connection error", "try again in a few seconds");
   }
}

void accountManage::searchForBike() {
    // Search for a bike in database and show all associated data about bike
   // hide(); // hide current view
    //myBikeWindow->show();
    myQHBox4->removeItem(myQVBox);
    removeActiveWindows();
    isBikeWindowActive = true;
    myBikeWindow = new bikeWindow();
    resize(800,500);
    myBikeWindow->queryAccess(query);
    myQHBox4->addWidget(myBikeWindow);
    myQHBox4->addLayout(myQVBox);
}

void accountManage::displayStatistics() {
    myQHBox4->removeItem(myQVBox);
    removeActiveWindows();
    this->resize(1550,900);
    mStat = new Statistics();
    isStatisticsActice = true;
    mStat->sendAccess(query);
    myQHBox4->addWidget(mStat);
    myQHBox4->addLayout(myQVBox);
}

void accountManage::queryAccess(QSqlQuery *a) {
    query = a;
}

void accountManage::removeActiveWindows() {
    if (isAddBikeActive) {
        myQHBox4->removeWidget(myBikeWindow2);
        delete myBikeWindow2;
        isAddBikeActive = false;
    }
    if (isBikeWindowActive) {
        myQHBox4->removeWidget(myBikeWindow);
        delete myBikeWindow;
        isBikeWindowActive  = false;
    }
    if (isStatisticsActice) {
       myQHBox4->removeWidget(mStat);
       delete mStat;
       isStatisticsActice = false;
    }
}

void accountManage::accessBikeWindow(int bid) {
    myQHBox4->removeItem(myQVBox);
    removeActiveWindows();
    myBikeWindow2 = new bikeWindow();
    isAddBikeActive = true;
    myBikeWindow2->queryAccess(query);
    myBikeWindow2->displayBikeInfo(bid);
    myQHBox4->addWidget(myBikeWindow2);
    myQHBox4->addLayout(myQVBox);
    this->show();
}
