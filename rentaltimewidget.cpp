#include "rentaltimewidget.h"
#include <QPushButton>
#include <QDateTime>

/*
 * Class used to display the rental period of a bike.
 * Setup rentalTimeWidget widget layout
 */
rentalTimeWidget::rentalTimeWidget()
{
    QLabel *rentalTimeLbl = new QLabel();
    rentalTimeLbl->setText("Rental time");
    rentalTimeLbl->setFont(QFont("Times", 16, QFont::Bold));
    myQVBox = new QVBoxLayout();
    rentalTimeUpdateLbl = new QLabel();
    myQVBox->addWidget(rentalTimeLbl);
    myQVBox->addWidget(rentalTimeUpdateLbl);

    setLayout(myQVBox);
}

/*
 * Function used to set the rental time label of a given int value
 */
void rentalTimeWidget::setData(int val) {
    QString rentalTime(QDateTime::fromTime_t(val).toUTC().toString("hh:mm"));
    rentalTimeUpdateLbl->setText(rentalTime);
}
