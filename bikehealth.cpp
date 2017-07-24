#include "bikehealth.h"
#include <QMessageBox>

bikeHealth::bikeHealth(int id)
{
    BikeId = id;
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
    QString statement = "UPDATE Master SET Health = ";
    statement.append(QString(val));
    statement.append("WHERE BikeId = ");
    statement.append(QString::fromStdString(std::to_string(BikeId)));
    if (!query.exec(statement))  QMessageBox::warning(this, "Connection error", "try again in a few seconds");
}

void bikeHealth::setData(int val) {
    val = val + (10/2);
    val -= val % 10;
    healthBar->setValue(val*10);
    healthSlider->setValue(val*10);
    //update server
    QString statement = "UPDATE Master SET Health = ";
    statement.append(QString(val));
    statement.append("WHERE BikeId = ");
    statement.append(QString::fromStdString(std::to_string(BikeId)));
    if (!query.exec(statement))  QMessageBox::warning(this, "Connection error", "try again in a few seconds");
}

void bikeHealth::sendQuery(QSqlQuery a) {
    query = a;
}
