#include "bikehealth.h"
#include <QMessageBox>

/*
 * Class used to diplay and allow user to change bike health.
 * Setup bikeHealth widget view given bikeId
 */
bikeHealth::bikeHealth(int id)
{
    BikeId = id;
    myQVBox = new QVBoxLayout();
    QLabel *lblHealth = new QLabel("Bike Health");
    lblHealth->setFont(QFont("Times", 16, QFont::Bold));
    myQVBox->addWidget(lblHealth);

    healthSlider = new QSlider(Qt::Horizontal);
    healthSlider->setMaximum(10);

    healthBar = new QProgressBar();
    healthBar->setMaximum(10);
    myQVBox->addWidget(healthSlider);
    myQVBox->addWidget(healthBar);
    myQVBox->setAlignment(Qt::AlignTop);

    // Connect button widgets to a handler function
    connect(healthSlider, &QSlider::sliderReleased, this, &bikeHealth::changeHealth);
    setLayout(myQVBox);
}

/*
 * Function to handle updating the bike health when slider value is changed.
 * Set the UI to display the changed health and update the server
 */
void bikeHealth::changeHealth() {
    int val = healthSlider->value();
    healthBar->setValue(val);
    QString statement = "UPDATE Master SET Health = ";
    statement.append(QString::fromStdString(std::to_string(val)));
    statement.append(" WHERE BikeId = ");
    statement.append(QString::fromStdString(std::to_string(BikeId)));
    if (!query->exec(statement))  {
        QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    }
}

/*
 * Function to set the bike health from a specified value.
 * Display it in the UI and update the server
 */
void bikeHealth::setData(int val) {
    healthBar->setValue(val);
    healthSlider->setValue(val);
    //update server
    QString statement = "UPDATE Master SET Health = ";
    statement.append(QString::fromStdString(std::to_string(val)));
    statement.append(" WHERE BikeId = ");
    statement.append(QString::fromStdString(std::to_string(BikeId)));
    if (!query->exec(statement))  {
        QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    }
}

/*
 * Give 'bikeHealth' access to QSqlQuery object.
 * Allow class to execute Sql statements to our server
 */
void bikeHealth::sendQuery(QSqlQuery *a) {
    query = a;
}
