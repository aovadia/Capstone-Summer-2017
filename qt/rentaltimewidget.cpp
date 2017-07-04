#include "rentaltimewidget.h"

rentalTimeWidget::rentalTimeWidget()
{
    QLabel *rentalTimeLbl = new QLabel();
    rentalTimeLbl->setText("Rental time");
    rentalTimeLbl->setFont(QFont("Times", 16, QFont::Bold));
    myQVBox = new QVBoxLayout();
    rentalTimeUpdateLbl = new QLabel(getRentalTime());
    myQVBox->addWidget(rentalTimeLbl);
    myQVBox->addWidget(rentalTimeUpdateLbl);

    setLayout(myQVBox);
}

QString rentalTimeWidget::getRentalTime() {
    // Server server for rental time
    // Return as a QString

    QString ret("2:00hrs"); //test
    return ret;
}
