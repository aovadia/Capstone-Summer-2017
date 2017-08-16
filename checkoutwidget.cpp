#include "checkoutwidget.h"
#include <QPushButton>
#include <QDateTime>
#include <QMessageBox>

/*
 * Class used to allow user to checkIn and checkOut bike.
 * Setup checkOutWidget widget layout
 */
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

    // Connect button widgets to a handler function
    connect(toggleCheckoutBtn, &QPushButton::released, this, &checkOutWidget::toggleCheckOut);
    setLayout(myQVBox);
}

/*
 * Function to handle when the 'toggleCheckoutBtn' button is pressed.
 * Toggle the checkOut/checkIn value of the bike and display it in the widget.
 * Also, add the new value to the 'checkInHistory' widget and update the server.
 */
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

/*
 * Function used to retrieve whether the bike is currently checked-in or checked-out to display it in the UI
 */
void checkOutWidget::setData(bool bCheckOut, QSqlQuery *a) {
    isCheckedOut = bCheckOut;
    query = a;
    if (bCheckOut) {
        checkOut->setText("Bike is checked-out");
    } else {
        checkOut->setText("Bike is checked-in");
    }
}
