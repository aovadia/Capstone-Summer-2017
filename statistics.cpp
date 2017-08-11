#include "statistics.h"
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QHeaderView>
#include "bikewindow.h"
#include "accountmanage.h"

Statistics::Statistics()
{
    for (int a = 0; a <= 205; a++) {
        data.push_back(QString::fromStdString(std::to_string(a)));
    }

    QStringList mHeaders;
    compute = new Analyzer(query);

    mainLayout = new QVBoxLayout();
    buttonLayout = new QVBoxLayout();
    mTable = new QTableWidget();
    buttonLayoutHorizontal = new QHBoxLayout();
    buttonLayoutHorizontal2  = new QHBoxLayout();
    buttonLayoutHorizontal3  = new QHBoxLayout();

    mTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mTable->setRowCount(200);
    mTable->setColumnCount(8);
    //mTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    mTable->setAlternatingRowColors(true);

    mainLayout->addWidget(mTable);

    setLayout(mainLayout);

    QPushButton *bCheckedIn = new QPushButton();
    bCheckedIn->setText("Bikes checked in");

    QPushButton *bCheckedOut = new QPushButton();
    bCheckedOut->setText("Bikes checked out");


    QPushButton *bActive = new QPushButton();
    bActive->setText("Bikes active");

    QPushButton *bInService = new QPushButton();
    bInService->setText("Bikes in service");

    QPushButton *bHealthAbove = new QPushButton();
    bHealthAbove->setText("Bike health above 5");

    QPushButton *bHealthBelow = new QPushButton();
    bHealthBelow->setText("Bike health below 5");

    QPushButton *bCheckedInDist = new QPushButton();
    bCheckedInDist->setText("Distance + Bike checked in");

    QPushButton *bCheckedOutDist = new QPushButton();
    bCheckedOutDist->setText("Distance + Bike checked out");

    QPushButton *bActiveDist = new QPushButton();
    bActiveDist->setText("Distance + Bikes active");

    QPushButton *bInServiceDist = new QPushButton();
    bInServiceDist->setText("Distance + Bikes in service");

    QPushButton *bHealthAboveDist = new QPushButton();
    bHealthAboveDist->setText("Distance + Bike health above 5");

    QPushButton *bHealthBelowDist = new QPushButton();
    bHealthBelowDist->setText("Distance + Bike health below 5");

    buttonLayoutHorizontal->addWidget(bCheckedIn);
    buttonLayoutHorizontal->addWidget(bCheckedOut);
    buttonLayoutHorizontal->addWidget(bHealthAbove);
    buttonLayoutHorizontal->addWidget(bHealthBelow);

    buttonLayoutHorizontal2->addWidget(bActive);
    buttonLayoutHorizontal2->addWidget(bInService);
    buttonLayoutHorizontal2->addWidget(bCheckedOutDist);
    buttonLayoutHorizontal2->addWidget(bCheckedInDist);

    buttonLayoutHorizontal3->addWidget(bActiveDist);
    buttonLayoutHorizontal3->addWidget(bInServiceDist);
    buttonLayoutHorizontal3->addWidget(bHealthBelowDist);
    buttonLayoutHorizontal3->addWidget(bHealthAboveDist);

    mainLayout->addLayout(buttonLayoutHorizontal);
    mainLayout->addLayout(buttonLayoutHorizontal2);
    mainLayout->addLayout(buttonLayoutHorizontal3);


    connect(bCheckedIn, &QPushButton::released, this, &Statistics::setCheckIn);
    connect(bCheckedOut, &QPushButton::released, this, &Statistics::setCheckOut);

    connect(bActive, &QPushButton::released, this, &Statistics::setActive);
    connect(bInService, &QPushButton::released, this, &Statistics::setInService);

    connect(bHealthAbove, &QPushButton::released, this, &Statistics::setHealthAbove);
    connect(bHealthBelow, &QPushButton::released, this, &Statistics::setHealthBelow);

    connect(bCheckedInDist, &QPushButton::released, this, &Statistics::setCheckInDist);
    connect(bCheckedOutDist, &QPushButton::released, this, &Statistics::setCheckOutDist);

    connect(bActiveDist, &QPushButton::released, this, &Statistics::setActiveDist);
    connect(bInServiceDist, &QPushButton::released, this, &Statistics::setInServiceDist);

    connect(bHealthAboveDist, &QPushButton::released, this, &Statistics::setHealthAboveDist);
    connect(bHealthBelowDist, &QPushButton::released, this, &Statistics::setHealthBelowDist);

    connect(mTable, &QTableWidget::doubleClicked, this, &Statistics::handleDoubleClicked);

    this->resize(1500, 1000);
    this->setWindowTitle("Bike Statistics");
}


void Statistics::setCheckIn() {
    Analyzer data(query);
    QVector<QString> value = data.TotalBikesCheckedIn();
    if (value[0] == NULL) {
        QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    } else if (value[0] == "None Found") {
        QMessageBox::warning(this, "Warninn", "No bikes on the server match the option");
    } else {
        setTable(value);
    }
}

void Statistics::setCheckOut() {
    Analyzer data(query);
    QVector<QString> value = data.TotalBikesCheckedOut();
    if (value[0] == NULL) {
        QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    } else if (value.at(0) == "None found") {
        QMessageBox::warning(this, "Warning", "No bikes on the server match the option");
    } else {
        setTable(value);
    }
}

void Statistics::setActive() {
    Analyzer data(query);
    QVector<QString> value = data.TotalBikesActive();
    if (value[0] == NULL) {
        QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    } else if (value.at(0) == "None found") {
        QMessageBox::warning(this, "Warning", "No bikes on the server match the option");
    } else {
        setTable(value);
    }
}

void Statistics::setInService() {
    Analyzer data(query);
    QVector<QString> value = data.TotalBikesInService();
    if (value[0] == NULL) {
        QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    } else if (value.at(0) == "None found") {
        QMessageBox::warning(this, "Warning", "No bikes on the server match the option");
    } else {
        setTable(value);
    }

}

void Statistics::setHealthAbove() {
    Analyzer data(query);
    QVector<QString> value = data.TotalBikesAbove5();
    if (value[0] == NULL) {
        QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    } else if (value.at(0) == "None found") {
        QMessageBox::warning(this, "Warning", "No bikes on the server match the option");
    } else {
        setTable(value);
    }
}

void Statistics::setHealthBelow() {
    Analyzer data(query);
    QVector<QString> value = data.TotalBikesBelow5();
    if (value[0] == NULL) {
        QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    } else if (value.at(0) == "None found") {
        QMessageBox::warning(this, "Warning", "No bikes on the server match the option");
    } else {
        setTable(value);
    }}

void Statistics::setCheckInDist() {
    Analyzer data(query);
    QVector<QString> value = data.DistanceBikesCheckedIn();
    if (value[0] == NULL) {
        QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    } else if (value.at(0) == "None found") {
        QMessageBox::warning(this, "Warning", "No bikes on the server match the option");
    } else {
        setTableTwoColumns(value);
    }
}

void Statistics::setCheckOutDist() {
    Analyzer data(query);
    QVector<QString> value = data.DistanceBikesCheckedOut();
    if (value[0] == NULL) {
        QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    } else if (value.at(0) == "None found") {
        QMessageBox::warning(this, "Warning", "No bikes on the server match the option");
    } else {
        setTableTwoColumns(value);
    }
}

void Statistics::setActiveDist() {
    Analyzer data(query);
    QVector<QString> value = data.DistanceBikesActive();
    if (value[0] == NULL) {
        QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    } else if (value.at(0) == "None found") {
        QMessageBox::warning(this, "Warning", "No bikes on the server match the option");
    } else {
        setTableTwoColumns(value);
    }
}

void Statistics::setInServiceDist() {
    Analyzer data(query);
    QVector<QString> value = data.DistanceBikesInService();
    if (value[0] == NULL) {
        QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    } else if (value.at(0) == "None found") {
        QMessageBox::warning(this, "Warning", "No bikes on the server match the option");
    } else {
        setTableTwoColumns(value);
    }
}

void Statistics::setHealthAboveDist() {
    Analyzer data(query);
    QVector<QString> value = data.DistanceBikesAbove5();
    if (value[0] == NULL) {
        QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    } else if (value.at(0) == "None found") {
        QMessageBox::warning(this, "Warning", "No bikes on the server match the option");
    } else {
        setTableTwoColumns(value);
    }}

void Statistics::setHealthBelowDist() {
    Analyzer data(query);
    QVector<QString> value = data.DistanceBikesBelow5();
    if (value[0] == NULL) {
        QMessageBox::warning(this, "Connection error", "try again in a few seconds");
    } else if (value.at(0) == "None found") {
        QMessageBox::warning(this, "Warning", "No bikes on the server match the option");
    } else {
        setTableTwoColumns(value);
    }}

void Statistics::setTable(QVector<QString> data) {
    mTable->setColumnCount(8);
    //mTable->horizontalHeader()->setDefaultSectionSize(175);
    mTable->clear(); // Remove existing entries
    int columnDivide = (data.size() / 8)+1;
    int counter = 0, pos = 0;
    mTable->setRowCount(columnDivide);
    for (int a = 0; a < data.size(); a++) {
        if (counter == 8) {
            pos++;
            counter = 0;
        }
        QTableWidgetItem *item = new QTableWidgetItem(data[a]);
        item->setTextAlignment(Qt::AlignCenter);
        mTable->setItem(pos, counter, item);
        counter++;
    }
}

void Statistics::setTableTwoColumns(QVector<QString> data) {
    mTable->clear(); // Remove existing entries
    mTable->setColumnCount(8);
    QStringList mHeaders;
    mHeaders.push_back("BikeId");
    mHeaders.push_back("Distance");
    mHeaders.push_back("");
    mHeaders.push_back("BikeId");
    mHeaders.push_back("Distance");
    mHeaders.push_back("");
    mHeaders.push_back("BikeId");
    mHeaders.push_back("Distance");
    mTable->setHorizontalHeaderLabels(mHeaders);

    int columnDivide = (data.size() / 6) +1;
    int counter = 0, pos = 0;
    mTable->setRowCount(columnDivide);
    for (int a = 0; a < data.size() -1; a+=2) {
        if (pos == 9) {
            pos = 0;
            counter++;
        }
        QTableWidgetItem *item = new QTableWidgetItem(data[a]);
        item->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *item2 = new QTableWidgetItem(data[a+1]);
        item2->setTextAlignment(Qt::AlignCenter);
        mTable->setItem(counter, pos,  item);
        mTable->setItem(counter, pos+1,  item2);
        qDebug() <<"Counter, pos, item: " << counter <<"  " << pos <<"    " <<data[a];
        qDebug() <<"Counter, pos, item: " << counter <<"  " << pos+1 <<"    " <<data[a+1];
        pos+=3;

    }
    mTable->resizeColumnToContents(2);
    mTable->resizeColumnToContents(5);
    mTable->resizeColumnToContents(5);
}


void Statistics::handleDoubleClicked() {
    QTableWidgetItem *test = mTable->item(mTable->currentRow(), mTable->currentColumn());
    if (!test ||!test->text().isEmpty()) {
        accountManage *myManage = new accountManage();
        myManage->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        myManage->queryAccess(query);
        myManage->accessBikeWindow(mTable->currentItem()->text().toInt());

    }
}

void Statistics::sendAccess(QSqlQuery *a) {
    query = a;
    //accoutMWindow = b;
}
