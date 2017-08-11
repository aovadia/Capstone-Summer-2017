#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QDateTime>

QVector<QDateTime> randomTimes();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("capstone-bikes.cphpxguj45gw.us-east-1.rds.amazonaws.com");
    db.setUserName("db_admin");
    db.setPassword("capstone");
    db.setPort(3306);
    db.setDatabaseName("Capstone_Bike_Shop");
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=15");
    if(!db.open()) {
           QSqlError err = db.lastError();
           qDebug() << err.text();
    }
    QSqlQuery *query = new QSqlQuery(db);

    QString statement = "SELECT COUNT(*) FROM Master";
    query->exec(statement);
    query->next();
    int max = query->value(0).toInt();


    for (int a = 3; a < max; a++) {

        QVector<QDateTime> val  = randomTimes();
        for (int b = 0; b < val.size()-1; b+=2) {
            QString update = "INSERT INTO Rentals (BikeId, Rented, Returned, RentalPlan) VALUES (";
           // qDebug() << a << val.at(b).toString() << val.at(b++).toString() << std::rand() % 9000 +1;
            update.append(QString::fromStdString(std::to_string(a)));
            update.append(", '");
            update.append(val.at(b).toString("yyyy-MM-dd hh:mm:ss"));
            update.append("'");
            b++;
            update.append(", '");
            update.append(val.at(b).toString("yyyy-MM-dd hh:mm:ss"));
            update.append("', ");
            update.append(QString::fromStdString(std::to_string(std::rand() % 9000 +1)));
            update.append(")");
            qDebug() <<update;
            query->exec(update);
        }
    }

    return a.exec();

}

QVector<QDateTime> randomTimes() {
    QVector<QDateTime> data;
    for (int a = 0; a <std::rand() % 100 +1; a++) {
        data.push_back(QDateTime::fromSecsSinceEpoch(std::rand()));
        data.push_back(QDateTime::fromSecsSinceEpoch(std::rand()));

    }
    std::sort(data.begin(), data.end());
    for (int a = 0; a < data.size(); a++) {
        qDebug() <<data.at(a).toString();
    }
    return data;
}
