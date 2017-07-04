#include "checkoutwidget.h"
#include <QPushButton>

checkOutWidget::checkOutWidget()
{
    myQVBox = new QVBoxLayout();
    checkOut = new QLabel(getCheckOutData());
    checkOut->setFont(QFont("Times", 16, QFont::Bold));
    myQVBox->addWidget(checkOut);

    QPushButton *toggleCheckoutBtn = new QPushButton("Toggle CheckOut");
    myQVBox->addWidget(toggleCheckoutBtn);
    connect(toggleCheckoutBtn, &QPushButton::released, this, &checkOutWidget::toggleCheckOut);
    setLayout(myQVBox);

}

void checkOutWidget::toggleCheckOut() {
    if (isCheckedOut) {
        isCheckedOut = false;
        checkOut->setText("Bike is Checked-in");
        // Update server
    } else {
        isCheckedOut = true;
        checkOut->setText("Bike is Checked-out");
        // Update server
    }
}

QString checkOutWidget::getCheckOutData() {
    // Access server to see if bike is checked-in or checked-out
    // Set bool 'isCheckedOut'
    QString bCout("Bike is Checked-out");
    QString bCin("Bike is Checked-in");
    if (isCheckedOut) {
          return bCout;
    } else {
        return bCin;
    }
}
