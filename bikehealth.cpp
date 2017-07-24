#include "bikehealth.h"

bikeHealth::bikeHealth()
{
    myQVBox = new QVBoxLayout();
    QLabel *lblHealth = new QLabel("Bike Health");
    lblHealth->setFont(QFont("Times", 16, QFont::Bold));
    myQVBox->addWidget(lblHealth);

    healthSlider = new QSlider(Qt::Horizontal);
    healthSlider->setMaximum(100);

    healthBar = new QProgressBar();
    setHealth();
    myQVBox->addWidget(healthSlider);
    myQVBox->addWidget(healthBar);
    myQVBox->setAlignment(Qt::AlignTop);
    // Double press checkin data to copy item to clipboard
    connect(healthSlider, &QSlider::sliderReleased, this, &bikeHealth::changeHealth);
    setLayout(myQVBox);
}

void bikeHealth::setHealth() {
    // Get health info from server and set it
    healthBar->setValue(10); //test
}

void bikeHealth::changeHealth() {
    int val = healthSlider->value();
    // Only allow increments of 10
    val = val + (10/2);
    val -= val % 10;
    healthBar->setValue(val);
}

void bikeHealth::setData(int val) {
    val = val + (10/2);
    val -= val % 10;
    healthBar->setValue(val*10);
    healthSlider->setValue(val*10);
    //update server
}

void bikeHealth::sendQuery(QSqlQuery a) {
    query = a;
}
