#include "checkoutwidget.h"
#include <QPushButton>
#include <QDateTime>
#include <QMessageBox>

checkOutWidget::checkOutWidget(checkInHistory *history, int id)
{
    BikeId = id;
    mTimeLine = history;
    myQVBox = new QVBoxLayout();
    checkOut = new QLabel();
    checkOut->setFont(QFont("Times", 16, QFont::Bold));
    myQVBox->addWidget(checkOut);

    QPushButton *toggleCheckoutBtn = new QPushButton("Toggle CheckOut");
    myQVBox->addWidget(toggleCheckoutBtn);
    connect(toggleCheckoutBtn, &QPushButton::released, this, &checkOutWidget::toggleCheckOut);
    setLayout(myQVBox);
}

void checkOutWidget::toggleCheckOut() {
    bool Serviced = false;
    QString statement = "SELECT Service FROM Master WHERE BikeId = ";
    statement.append(QString::fromStdString( std::to_string(BikeId)));
    if (query->exec(statement)) {
        query->next();
        Serviced = query->value(0).toBool();
    }
    else QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    if (!Serviced) {
        if (isCheckedOut) {
            isCheckedOut = false;
            checkOut->setText("Bike is Checked-in");
            mTimeLine->setToggled(QDateTime::currentDateTime(), isCheckedOut, BikeId );
            // Update server
        }
        else {
            isCheckedOut = true;
            checkOut->setText("Bike is Checked-out");
            mTimeLine->setToggled(QDateTime::currentDateTime(), isCheckedOut, BikeId);
            // Update server
        }
    }
    else QMessageBox::warning(this, "Bike in service" ,"Bike is currently being serviced and cannot be checked out at this time");
}

void checkOutWidget::setData(bool bCheckOut, QSqlQuery *a) {
    isCheckedOut = bCheckOut;
    query = a;
    if (bCheckOut) {
        checkOut->setText("Bike is checked-out");
    } else {
        checkOut->setText("Bike is checked-in");
    }
}
