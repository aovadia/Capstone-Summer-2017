#include "bikeserviced.h"
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>

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

void bikeServiced::accessSql(QSqlQuery *a, int id) {
    query = a;
    bikeID = id;
}
