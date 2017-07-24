#include "bikeserviced.h"
#include <QPushButton>
#include <QMessageBox>

bikeServiced::bikeServiced(bikeHealth *myBikeHealth)
{
    this->myBikeHealth = myBikeHealth;
    myQVBox = new QVBoxLayout();
    serviced = new QLabel();
    serviced->setFont(QFont("Times", 16, QFont::Bold));

    myQVBox->addWidget(serviced);

    QPushButton *toggleServiced = new QPushButton("Toggle serviced status");
    myQVBox->addWidget(toggleServiced);

    connect(toggleServiced, &QPushButton::released, this, &bikeServiced::toggleInService);
    setLayout(myQVBox);
}


void bikeServiced::toggleInService() {
    if (inService) {
        serviced->setText("Bike is active");
        inService = false;
        myBikeHealth->setData(100);
    } else {
        serviced->setText("Bike is being serviced");
        inService = true;
    }
    // Reflect change in server
    QString statement = "UPDATE Master SET Serviced = '";
    statement.append(QString::fromStdString(std::to_string(inService)));
    statement.append("' WHERE BikeId = ");
    statement.append(QString::fromStdString(std::to_string(bikeID)));
    if (!query.exec(statement))  QMessageBox::warning(this, "Connection error", "try again in a few seconds");

}

void bikeServiced::setData(bool bServiced) {
    inService = bServiced;
    if (inService) {
        serviced->setText("Bike is being serviced");
    } else {
        serviced->setText("Bike is active");
    }
    QString statement = "UPDATE Master SET Serviced = '";
    statement.append(QString::fromStdString(std::to_string(inService)));
    statement.append("' WHERE BikeId = ");
    statement.append(QString::fromStdString(std::to_string(bikeID)));
    if (!query.exec(statement))  QMessageBox::warning(this, "Connection error", "try again in a few seconds");

}

void bikeServiced::accessSql(QSqlQuery a, int id) {
    query = a;
    bikeID = id;
}
