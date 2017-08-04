#include "checkoutwidget.h"
#include <QPushButton>
#include <QDateTime>
#include <QDebug>

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
    QVector<std::string> *b;
    if (isCheckedOut) {
        isCheckedOut = false;
        checkOut->setText("Bike is Checked-in");
        mTimeLine->setToggled(QDateTime::currentDateTime(), isCheckedOut,b, BikeId );
        // Update server
    } else {
        isCheckedOut = true;
        checkOut->setText("Bike is Checked-out");
        mTimeLine->setToggled(QDateTime::currentDateTime(), isCheckedOut,b, BikeId);
        // Update server
    }
}

void checkOutWidget::setData(bool bCheckOut) {
    isCheckedOut = bCheckOut;
    qDebug() <<"isCheckedOut: " <<isCheckedOut;

    if (bCheckOut) {
        checkOut->setText("Bike is checked-out");
    } else {
        checkOut->setText("Bike is checked-in");
    }
}
