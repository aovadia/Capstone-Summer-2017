#include "bikeserviced.h"
#include <QPushButton>

bikeServiced::bikeServiced(bikeHealth *myBikeHealth)
{
    this->myBikeHealth = myBikeHealth;
    myQVBox = new QVBoxLayout();
    serviced = new QLabel();
    serviced->setFont(QFont("Times", 16, QFont::Bold));
    checkInService();
    if (inService) {
        serviced->setText("Bike is being serviced");
    } else {
        serviced->setText("Bike is active");
    }
    myQVBox->addWidget(serviced);

    QPushButton *toggleServiced = new QPushButton("Toggle serviced status");
    myQVBox->addWidget(toggleServiced);

    connect(toggleServiced, &QPushButton::released, this, &bikeServiced::toggleInService);
    setLayout(myQVBox);
}

void bikeServiced::checkInService() {
    // Using BikeID, check server to see if bike is in service
    // set 'inService' bool to true/false
}

void bikeServiced::toggleInService() {
    if (inService) {
        serviced->setText("Bike is active");
        inService = false;
        myBikeHealth->setBikeServicedHealth(100);
    } else {
        serviced->setText("Bike is being serviced");
        inService = true;
    }
    // Reflect change in server
}
