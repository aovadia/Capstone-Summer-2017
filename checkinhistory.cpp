#include "checkinhistory.h"
#include <QDebug>
#include <QClipboard>
#include <QApplication>
#include <QDateTime>
#include <QMessageBox>
#include <QPushButton>

checkInHistory::checkInHistory(const int id, rentalTimeWidget *a)
{
    mTimeWidget = a;
    bikeID = id;
    myQVBox = new QVBoxLayout();
    QLabel *checkin = new QLabel("Checkin / Checkout info",this);
    checkin->setFont(QFont("Times", 16, QFont::Bold));

    myQVBox->addWidget(checkin);

    myList = new QListWidget(this);
    myList->setMinimumWidth(375);
    myList->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    myQVBox->addWidget(myList);
   // myQHBox->addSpacerItem(horiSpace);
    setLayout(myQVBox);
}

// Method to copy item to clipboard
void checkInHistory::copyCheckInData() {
    int pos = myList->currentRow();
    qDebug() <<"pos: " <<QString::number(pos);
    QClipboard *copyItem = QApplication::clipboard();
    copyItem->setText(myList->currentItem()->text());

}

void checkInHistory::testEnterCheckinData() {
    myList->addItem("Out: 2/2/17 5:30am");
    myList->addItem("In: 2/2/17 7:45am");
    myList->addItem("Out: 2/2/17 5:30am");
    myList->addItem("In: 2/2/17 7:45am");
    myList->addItem("Out: 2/2/17 5:30am");
    myList->addItem("In: 2/2/17 7:45am");
}

void checkInHistory::setData(QVector<std::string> data) {
    myList->clear();
    std::string Year, Month, Day, Time, Status;
    for (int a = 0; a < data.size(); a++) {
        qDebug() <<"SetData string: "<<QString::fromStdString(data[a]);
        Year = data[a].substr(0, 4);
        Month = data[a].substr(5, 2);
        Day = data[a].substr(8, 2);
        Time = data[a].substr(11, 8);
        if (data[a].back() == 'I') Status = "Checked In: ";
        else Status = "Checked Out: ";
        Status.append(Month);
        Status.append(".");
        Status.append(Day);
        Status.append(".");
        Status.append(Year);
        Status.append(" ");
        Status.append(Time);
        myList->addItem(QString::fromUtf8(Status.c_str()));
    }
}

bool checkInHistory::setToggled(QDateTime mTime, bool mCheckedOut, QVector<std::string> *data, int BikeId) {
    QString rentalIdQuery = "SELECT COUNT(*) FROM Rentals";
    if (!query->exec(rentalIdQuery)) QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    query->next();
    int RentalId = query->value(0).toInt();
    QString checkIn = "UPDATE Rentals SET Returned = '";
    QString checkInEnd = " WHERE RentalID = ";
    QString checkIn2 = "UPDATE Master SET CheckedOut = 0 WHERE BikeId = ";
    QString checkOut = "INSERT INTO Rentals (BikeId, Rented, Returned, RentalPlan) VALUES (";
    QString checkOutEnd = ")";
    QString checkOut2 = "UPDATE Master SET CheckedOut = 1 WHERE BikeId = ";
    QString DateTime = mTime.toString("yyyy-MM-dd hh:mm:ss");
    if (!mCheckedOut) {
        checkIn.append(DateTime);
        checkIn.append("'");
        checkIn.append(checkInEnd);
        checkIn.append(QString::fromStdString( std::to_string(RentalId)));
        qDebug() <<"checkin statement: " <<checkIn;
        if (!query->exec(checkIn)) QMessageBox::warning(this, "Connection error", "try again in a few seconds");
        checkIn2.append(QString::fromStdString( std::to_string(BikeId)));
        if(!query->exec(checkIn2)) QMessageBox::warning(this, "Connection error", "try again in a few seconds");

    }
    else {
        setRentalTime();
        mTimeWidget->setData(RentalPlan);
        checkOut.append(QString::fromStdString( std::to_string(BikeId)));
        checkOut.append(", '");
        checkOut.append(DateTime);
        checkOut.append("', ");
        checkOut.append("NULL, ");
        checkOut.append(QString::fromStdString( std::to_string(RentalPlan)));
        checkOut.append(checkOutEnd);
        qDebug() <<"checkout statement: " <<checkOut;
        if (!query->exec(checkOut)) QMessageBox::warning(this, "Connection error", "try again in a few seconds");
        checkOut2.append(QString::fromStdString( std::to_string(BikeId)));
        if(!query->exec(checkOut2)) QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    }
    updateList(BikeId);
    return false;
}

void checkInHistory::updateList(int BikeId) {
    QVector<std::string> timeline;
    QString val = QString::fromStdString(std::to_string(BikeId));
    bool firstTimeDone;
    QString statement = "SELECT * FROM Rentals WHERE BikeId = ";
    statement.append(val);
    statement.append(" ORDER BY RentalId DESC");
    bool receivedRental;
    if (query->exec(statement)) {
        receivedRental = true;
        while (query->next()) {
            if (!firstTimeDone) {
                firstTimeDone = true;
            }
            if (query->value(3).toString() != NULL) {
                timeline.push_back(query->value(3).toString().toStdString().append("I")); //append I
            }
            timeline.push_back(query->value(2).toString().toStdString());
        }
    }
    else QMessageBox::warning(this, "Connection error", "try again in a few seconds");

    for (int a = 0; a < timeline.size(); a++) {
        for (int b = 0; b < timeline[a].size(); b++) {
            if (timeline[a][b] == 'T') timeline[a][b] = ' ';
        }
        qDebug() <<"timeline: " <<QString::fromUtf8(timeline[a].c_str());
        setData(timeline);
    }


}

void checkInHistory::sendQuery(QSqlQuery *a) {
    query = a;
}


void checkInHistory::setRentalTime() {
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
    connect(accept, &QPushButton::released, this, &checkInHistory::saveRentalTime);
    mDialog->exec();
}

void checkInHistory::saveRentalTime() {
    // Update server
    std::string val = mComboBox->currentText().toStdString();
    std::string hh = val.substr(0,2);
    std::string mm = val.substr(3,2);
    int hh2 = std::atoi(hh.c_str());
    int  mm2 = std::atoi(mm.c_str());
    int timeTotal = mm2*60 + hh2*3600;
    RentalPlan = timeTotal;
    mDialog->close();
}
