#include "checkinhistory.h"
#include <QDebug>
#include <QClipboard>
#include <QApplication>

checkInHistory::checkInHistory(const int id)
{
    bikeID = id;
    myQVBox = new QVBoxLayout();
    QLabel *checkin = new QLabel("Checkin / Checkout info",this);
    checkin->setFont(QFont("Times", 16, QFont::Bold));

    myQVBox->addWidget(checkin);

    myList = new QListWidget(this);
    myList->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    myQVBox->addWidget(myList);
   // myQHBox->addSpacerItem(horiSpace);
    testEnterCheckinData();
    setLayout(myQVBox);
}

// Method to copy item to clipboard
void checkInHistory::copyCheckInData() {
    int pos = myList->currentRow();
    qDebug() <<"pos: " <<QString::number(pos);
    QClipboard *copyItem = QApplication::clipboard();
    copyItem->setText(myList->currentItem()->text());

}

void checkInHistory::enterCheckinData() {
    /* TODO
     * Get Check in/out data from server
     * add Items to 'myList' using the addItem() or addItems() method
     */

}

void checkInHistory::testEnterCheckinData() {
    myList->addItem("Out: 2/2/17 5:30am");
    myList->addItem("In: 2/2/17 7:45am");
    myList->addItem("Out: 2/2/17 5:30am");
    myList->addItem("In: 2/2/17 7:45am");
    myList->addItem("Out: 2/2/17 5:30am");
    myList->addItem("In: 2/2/17 7:45am");
}
