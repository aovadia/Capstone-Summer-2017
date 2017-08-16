#include "analyzer.h"
#include <QDebug>

//constructor which allows passing along of active query object
Analyzer::Analyzer(QSqlQuery *a)
{
query = a;
}

//Returns a list of checked-in bikes
QVector<QString> Analyzer::TotalBikesCheckedIn() {
    //Query is constructed from prefabricated strings
    QVector<QString> result;
    QString statement = select1;
    statement.append(from);
    statement.append(where);
    statement.append("CheckedOut = 0");
    bool querySuccess = false;
    //Execution of query
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) {
            result.push_back(query->value(0).toString());
        }
    } else {
        qDebug() <<"Analyze failed!"; //internal use
    }
    if (querySuccess && result.empty()) result.push_back( "None found"); //to differentiate from connection error

    return result;
}

//Returns a list of checked-out bikes
//This function and the 4 following work in pretty much the same way as the previous function
//The query is different to reflect the search.
//After these functions, there are functions that look for 2 paramaters, that are more intricate
QVector<QString> Analyzer::TotalBikesCheckedOut() {
    QVector<QString> result;
    QString statement = select1;
    statement.append(from);
    statement.append(where);
    statement.append("CheckedOut = 1");
    bool querySuccess = false;
    qDebug() << "Analyze statement: " <<statement;

    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) {
            qDebug() <<"checkout: " <<query->value(0).toString();
            result.push_back(query->value(0).toString());
        }
    }
    if (querySuccess && result.empty()) result.push_back("None found");
    return result;
}

//Returns a list of bikes in service
QVector<QString> Analyzer::TotalBikesInService() {
    QVector<QString> result;
    QString statement = select1;
    statement.append(from);
    statement.append(where);
    statement.append("Service = 1");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) result.push_back(query->value(0).toString());
    }
    if (querySuccess && result.empty()) result.push_back( "None found");
    return result;
}

//Returns a list of bikes not in service
QVector<QString> Analyzer::TotalBikesActive() {
    QVector<QString> result;
    QString statement = select1;
    statement.append(from);
    statement.append(where);
    statement.append("Service = 0");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) result.push_back(query->value(0).toString());
    }
    if (querySuccess && result.empty()) result.push_back( "None found");
    return result;
}


//Returns a list of the healthier bikes
QVector<QString> Analyzer::TotalBikesAbove5() {
    QVector<QString> result;
    QString statement = select1;
    statement.append(from);
    statement.append(where);
    statement.append("Health >= 5");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) result.push_back(query->value(0).toString());
    }
    if (querySuccess && result.empty()) result.push_back( "None found");
    return result;
}

//Returns a list of the less healthy bikes
QVector<QString> Analyzer::TotalBikesBelow5() {
    QVector<QString> result;
    QString statement = select1;
    statement.append(from);
    statement.append(where);
    statement.append("Health < 5");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) result.push_back(query->value(0).toString());
    }
    if (querySuccess && result.empty()) result.push_back( "None found");
    return result;
}


// The next six functions return an additional parameter, distance traveled of the bike.
// This requires additional formatting

//Returns a list of bikes checked in with distances
QVector<QString> Analyzer::DistanceBikesCheckedIn() {
    //Creation of query
    QVector<QString> result;
    QString statement = select2;
    statement.append(from);
    statement.append(where);
    statement.append("CheckedOut = 0");
    bool querySuccess = false;
    //Execution of query
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) {
            result.push_back(query->value(0).toString());
            double  Distance = query->value(1).toDouble();
            //Formatting into kilometers and meters
            int kilometers = Distance / 1;
            double meters = ((Distance - kilometers) * 1000);
            QString text;
            if (kilometers) {
                text.append(QString::fromStdString(std::to_string(kilometers)));
                text.append(" km ");
            }
            if (meters) {
                text.append(QString::number(meters, 'f', 2));
                text.append(" m");
            }
            if (!kilometers && !meters) {
                text.append("0 m");
            }
            result.push_back(text);
        }
    }
    if (querySuccess && result.empty()) result.push_back( "None found"); //to differentiate from connection
    return result;
}

//The rest of the distance functions follow the same pattern as the first

//Returns a list of bikes checked out with distances
QVector<QString> Analyzer::DistanceBikesCheckedOut() {
    QVector<QString> result;
    QString statement = select2;
    statement.append(from);
    statement.append(where);
    statement.append("CheckedOut = 1");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) {
            result.push_back(query->value(0).toString());
            double  Distance = query->value(1).toDouble();
            int kilometers = Distance / 1;
            double meters = ((Distance - kilometers) * 1000);
            QString text;
            if (kilometers) {
                text.append(QString::fromStdString(std::to_string(kilometers)));
                text.append(" km ");
            }
            if (meters) {
                text.append(QString::number(meters, 'f', 2));
                text.append(" m");
            }
            if (!kilometers && !meters) {
                text.append("0 m");
            }
            result.push_back(text);
        }
    }
    if (querySuccess && result.empty()) result.push_back( "None found");
    return result;
}

//Returns a list of bikes in service with distances
QVector<QString> Analyzer::DistanceBikesInService() {
    QVector<QString> result;
    QString statement = select2;
    statement.append(from);
    statement.append(where);
    statement.append("Service = 1");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) {
            result.push_back(query->value(0).toString());
            double  Distance = query->value(1).toDouble();
            int kilometers = Distance / 1;
            double meters = ((Distance - kilometers) * 1000);
            QString text;
            if (kilometers) {
                text.append(QString::fromStdString(std::to_string(kilometers)));
                text.append(" km ");
            }
            if (meters) {
                text.append(QString::number(meters, 'f', 2));
                text.append(" m");
            }
            if (!kilometers && !meters) {
                text.append("0 m");
            }
            result.push_back(text);
        }
    }
    if (querySuccess && result.empty()) result.push_back( "None found");
    return result;
}

//Returns a list of bikes not in service with distances
QVector<QString> Analyzer::DistanceBikesActive() {
    QVector<QString> result;
    QString statement = select2;
    statement.append(from);
    statement.append(where);
    statement.append("Service = 0");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) {
            result.push_back(query->value(0).toString());
            double  Distance = query->value(1).toDouble();
            int kilometers = Distance / 1;
            double meters = ((Distance - kilometers) * 1000);
            QString text;
            if (kilometers) {
                text.append(QString::fromStdString(std::to_string(kilometers)));
                text.append(" km ");
            }
            if (meters) {
                text.append(QString::number(meters, 'f', 2));
                text.append(" m");
            }
            if (!kilometers && !meters) {
                text.append("0 m");
            }
            result.push_back(text);
        }
    }
    if (querySuccess && result.empty()) result.push_back( "None found");
    return result;
}

//Returns a list of more healthy bikes with distances
QVector<QString> Analyzer::DistanceBikesAbove5() {
    QVector<QString> result;
    QString statement = select2;
    statement.append(from);
    statement.append(where);
    statement.append("Health >= 5");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) {
            result.push_back(query->value(0).toString());
            double  Distance = query->value(1).toDouble();
            int kilometers = Distance / 1;
            double meters = ((Distance - kilometers) * 1000);
            QString text;
            if (kilometers) {
                text.append(QString::fromStdString(std::to_string(kilometers)));
                text.append(" km ");
            }
            if (meters) {
                text.append(QString::number(meters, 'f', 2));
                text.append(" m");
            }
            if (!kilometers && !meters) {
                text.append("0 m");
            }
            result.push_back(text);
        }
    }
    if (querySuccess && result.empty()) result.push_back( "None found");
    return result;
}
//Returns a list of less healthy bikes with distances
QVector<QString> Analyzer::DistanceBikesBelow5() {
    QVector<QString> result;
    QString statement = select2;
    statement.append(from);
    statement.append(where);
    statement.append("Health < 5");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) {
            result.push_back(query->value(0).toString());
            double  Distance = query->value(1).toDouble();
            int kilometers = Distance / 1;
            double meters = ((Distance - kilometers) * 1000);
            QString text;
            if (kilometers) {
                text.append(QString::fromStdString(std::to_string(kilometers)));
                text.append(" km ");
            }
            if (meters) {
                text.append(QString::number(meters, 'f', 2));
                text.append(" m");
            }
            if (!kilometers && !meters) {
                text.append("0 m");
            }
            result.push_back(text);
        }
    }
    if (querySuccess && result.empty()) result.push_back( "None found");
    return result;
}
