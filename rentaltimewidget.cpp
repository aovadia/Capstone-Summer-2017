#include "rentaltimewidget.h"
#include <QPushButton>
#include <QDateTime>

rentalTimeWidget::rentalTimeWidget()
{
    QLabel *rentalTimeLbl = new QLabel();
    rentalTimeLbl->setText("Rental time");
    rentalTimeLbl->setFont(QFont("Times", 16, QFont::Bold));
    myQVBox = new QVBoxLayout();
    rentalTimeUpdateLbl = new QLabel();
    myQVBox->addWidget(rentalTimeLbl);
    myQVBox->addWidget(rentalTimeUpdateLbl);
    QPushButton *setTime = new QPushButton("Set Rental Time");
    myQVBox->addWidget(setTime);
    connect(setTime, &QPushButton::released, this, &rentalTimeWidget::setRentalTime);
    setLayout(myQVBox);
}


void rentalTimeWidget::setRentalTime() {
    mDialog = new QDialog();
    QVBoxLayout *rentalLayout = new QVBoxLayout();
    mDialog->setLayout(rentalLayout);
    mDialog->setModal(true);
    mDialog->setWindowTitle("Set Rental Time");

    QLabel *mLabel = new QLabel("Set Rental Time (HH:MM)");
    rentalLayout->addWidget(mLabel);

    mComboBox = new QComboBox();
    // add options
    for (double a  = 15;  a < 48 *15; a+=15) {
        mComboBox->addItem(QDateTime::fromTime_t(a*60).toUTC().toString("hh:mm"));
    }
    rentalLayout->addWidget(mComboBox);

    QPushButton *accept = new QPushButton("Save");
    rentalLayout->addWidget(accept);
    connect(accept, &QPushButton::released, this, &rentalTimeWidget::saveRentalTime);
    mDialog->exec();
}

void rentalTimeWidget::saveRentalTime() {
    rentalTimeUpdateLbl->setText(mComboBox->currentText() + " hh:mm");

    // Update server

    mDialog->close();
}

void rentalTimeWidget::setData(int val) {
    QString rentalTime(QDateTime::fromTime_t(val).toUTC().toString("hh:mm"));
    rentalTimeUpdateLbl->setText(rentalTime);
}

