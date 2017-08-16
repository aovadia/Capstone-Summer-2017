#include "bikeserviced.h"
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>

/*
 * Class used to display and toggle if the bike is in-service or is active.
 * Setup bikeServiced widget layout given access to 'bikeHealth' widget
 */
bikeServiced::bikeServiced(bikeHealth *myBikeHealth)
{
    this->myBikeHealth = myBikeHealth;
    myQVBox = new QVBoxLayout();
    serviced = new QLabel();
    serviced->setFont(QFont("Times", 16, QFont::Bold));

    myQVBox->addWidget(serviced);

    QPushButton *toggleServiced = new QPushButton("Toggle serviced status");
    myQVBox->addWidget(toggleServiced);

    // Connect button widgets to a handler function
    connect(toggleServiced, &QPushButton::released, this, &bikeServiced::toggleInService);
    setLayout(myQVBox);
}

/*
 * Function to handle when the 'bikeServiced' button is pressed.
 * Check server to see if bike is in-service or is active.
 * Then flip the value and update the server.
 * If 'bikeService' is updated to be active, set bikeHealth to 100%
 */
void bikeServiced::toggleInService() {
    bool isCheckedOut = false;
    QString statement = "SELECT CheckedOut FROM Master Where BikeId = ";
    statement.append(QString::fromStdString(std::to_string(bikeID)));
    if (query->exec(statement)) {
        query->next();
        isCheckedOut = query->value(0).toBool();
    }
    else QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    if (!isCheckedOut) {
        if (inService) {
            serviced->setText("Bike is active");
            inService = false;
            myBikeHealth->setData(10);
        }
        else {
            serviced->setText("Bike is being serviced");
            inService = true;
        }
        // Reflect change in server
        statement = "UPDATE Master SET Service = '";
        statement.append(QString::fromStdString(std::to_string(inService)));
        statement.append("' WHERE BikeId = ");
        statement.append(QString::fromStdString(std::to_string(bikeID)));
        if (!query->exec(statement))  {
            QMessageBox::warning(this, "Connection error", "try again in a few seconds");
            qDebug() <<"Statement: " << statement;
        }
    }
    else QMessageBox::warning(this, "Bike Checked Out", "Bike must be returned to the shop in order to be serviced.");
}

/*
 * Function to set the initial value of 'bikeService' given a specified boolean
 * Update the server with 'serviced' value
 */
void bikeServiced::setData(bool bServiced) {
    inService = bServiced;
    if (inService) {
        serviced->setText("Bike is being serviced");
    } else {
        serviced->setText("Bike is active");
    }
    QString statement = "UPDATE Master SET Service = '";
    statement.append(QString::fromStdString(std::to_string(inService)));
    statement.append("' WHERE BikeId = ");
    statement.append(QString::fromStdString(std::to_string(bikeID)));
    if (!query->exec(statement))  {
        QMessageBox::warning(this, "Connection error", "try again in a few seconds");
        qDebug() <<"Statement: " << statement;
    }
}

/*
 * Give 'bikeServiced' access to QSqlQuery object.
 * Allow class to execute Sql statements to our server.
 * Set bikeId
 */
void bikeServiced::accessSql(QSqlQuery *a, int id) {
    query = a;
    bikeID = id;
}
