#include <QPushButton>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QMessageBox>
#include "accountmanage.h"

/*  Class used to setup the layout for creating a new bike,
 *  searching for a new bike, and displaying bike statistics.
 *  Setup account management page layout
 */
accountManage::accountManage(QWidget *parent) : QWidget(parent)
{
    isBikeWindowActive = false;
    isAddBikeActive = false;
    isStatisticsActice = false;

    myQVBox = new QVBoxLayout();
    this->resize(800,500); //set size of window
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

    // Connect button widgets to a handler function
    connect(newBike, &QPushButton::released,this, &accountManage::addNewBike);
    connect(searchBike, &QPushButton::released, this, &accountManage::searchForBike);
    connect(statBike, &QPushButton::released, this, &accountManage::displayStatistics);
}

/*
 * Function to handle the button to create a new bike.
 * Initialize the bikeId, checkOut, Service, Distance, Health of new bike to default values.
 * Enter new bike data into the server and open bikeWindow view for newly created bike
 */
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
            // Prevent creating multiple views on the same window
            myQHBox4->removeItem(myQVBox);
            removeActiveWindows();
            myBikeWindow2 = new bikeWindow(); // Create new bikeWindow
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

/*
 * Function to handle searching for a new bike.
 * Verify the bike exists on the server, and open a bikeWindow view
 */
void accountManage::searchForBike() {
    // Prevent creating multiple views on the same window
    myQHBox4->removeItem(myQVBox);
    removeActiveWindows();
    isBikeWindowActive = true;
    myBikeWindow = new bikeWindow(); // Create new bikeWindow view
    resize(800,500);
    myBikeWindow->queryAccess(query);
    myQHBox4->addWidget(myBikeWindow);
    myQHBox4->addLayout(myQVBox);
}

/*
 * Function to display bike statistics in a new window
 */
void accountManage::displayStatistics() {
    // Prevent creating multiple views on the same window
    myQHBox4->removeItem(myQVBox);
    removeActiveWindows();
    this->resize(1550,900);
    mStat = new Statistics(); // Create new Statistics window
    isStatisticsActice = true;
    mStat->sendAccess(query);
    myQHBox4->addWidget(mStat);
    myQHBox4->addLayout(myQVBox);
}

/*
 * Give 'accountManage' access to QSqlQuery object.
 * Allow class to execute Sql statements to our server
 */
void accountManage::queryAccess(QSqlQuery *a) {
    query = a;
}

/*
 * Function to remove current active windows from the current view.
 * Used to prevent multiple instances from appearing in the same window.
 */
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

/*
 * Function designed to allow the bike statistics page to launch a bikeWindow widget,
 * give the proper bikeId
 */
void accountManage::accessBikeWindow(int bid) {
    // Prevent creating multiple views on the same window
    myQHBox4->removeItem(myQVBox);
    removeActiveWindows();
    myBikeWindow2 = new bikeWindow(); // Create new bikeWindow
    isAddBikeActive = true;
    myBikeWindow2->queryAccess(query);
    myBikeWindow2->displayBikeInfo(bid);
    myQHBox4->addWidget(myBikeWindow2);
    myQHBox4->addLayout(myQVBox);
    this->show();
}
