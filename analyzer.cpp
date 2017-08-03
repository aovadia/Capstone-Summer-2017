#include "analyzer.h"

Analyzer::Analyzer(QSqlQuery *a)
{
query = a;
}

QVector<QString> Analyzer::TotalBikesCheckedIn() {
    QVector<QString> result;
    QString statement = select1;
    statement.append(from);
    statement.append(where);
    statement.append("CheckedOut = 0 ");
    statement.append(orderBy);
    statement.append("BikeId");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) result.push_back(query->value(0).toString());
    }
    if (querySuccess && result[0] == NULL) result[0] = "None found";
    return result;
}

QVector<QString> Analyzer::TotalBikesCheckedOut() {
    QVector<QString> result;
    QString statement = select1;
    statement.append(from);
    statement.append(where);
    statement.append("CheckedOut = 1 ");
    statement.append(orderBy);
    statement.append("BikeId");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) result.push_back(query->value(0).toString());
    }
    if (querySuccess && result[0] == NULL) result[0] = "None found";
    return result;
}

QVector<QString> Analyzer::TotalBikesInService() {
    QVector<QString> result;
    QString statement = select1;
    statement.append(from);
    statement.append(where);
    statement.append("Service = 1 ");
    statement.append(orderBy);
    statement.append("BikeId");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) result.push_back(query->value(0).toString());
    }
    if (querySuccess && result[0] == NULL) result[0] = "None found";
    return result;
}

QVector<QString> Analyzer::TotalBikesActive() {
    QVector<QString> result;
    QString statement = select1;
    statement.append(from);
    statement.append(where);
    statement.append("Service = 0 ");
    statement.append(orderBy);
    statement.append("BikeId");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) result.push_back(query->value(0).toString());
    }
    if (querySuccess && result[0] == NULL) result[0] = "None found";
    return result;
}

QVector<QString> Analyzer::TotalBikesAbove5() {
    QVector<QString> result;
    QString statement = select1;
    statement.append(from);
    statement.append(where);
    statement.append("Health >= 5 ");
    statement.append(orderBy);
    statement.append("BikeId");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) result.push_back(query->value(0).toString());
    }
    if (querySuccess && result[0] == NULL) result[0] = "None found";
    return result;
}

QVector<QString> Analyzer::TotalBikesBelow5() {
    QVector<QString> result;
    QString statement = select1;
    statement.append(from);
    statement.append(where);
    statement.append("Health < 5 ");
    statement.append(orderBy);
    statement.append("BikeId");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) result.push_back(query->value(0).toString());
    }
    if (querySuccess && result[0] == NULL) result[0] = "None found";
    return result;
}

QVector<QString> Analyzer::DistanceBikesCheckedIn() {
    QVector<QString> result;
    QString statement = select2;
    statement.append(from);
    statement.append(where);
    statement.append("CheckedOut = 0 ");
    statement.append(orderBy);
    statement.append("BikeId");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) {
            result.push_back(query->value(0).toString());
            result.push_back(query->value(1).toString());
        }
    }
    if (querySuccess && result[0] == NULL) result[0] = "None found";
    return result;
}

QVector<QString> Analyzer::DistanceBikesCheckedOut() {
    QVector<QString> result;
    QString statement = select2;
    statement.append(from);
    statement.append(where);
    statement.append("CheckedOut = 1 ");
    statement.append(orderBy);
    statement.append("BikeId");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) {
            result.push_back(query->value(0).toString());
            result.push_back(query->value(1).toString());
        }
    }
    if (querySuccess && result[0] == NULL) result[0] = "None found";
    return result;
}

QVector<QString> Analyzer::DistanceBikesInService() {
    QVector<QString> result;
    QString statement = select2;
    statement.append(from);
    statement.append(where);
    statement.append("Service = 1 ");
    statement.append(orderBy);
    statement.append("BikeId");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) {
            result.push_back(query->value(0).toString());
            result.push_back(query->value(1).toString());
        }
    }
    if (querySuccess && result[0] == NULL) result[0] = "None found";
    return result;
}

QVector<QString> Analyzer::DistanceBikesActive() {
    QVector<QString> result;
    QString statement = select2;
    statement.append(from);
    statement.append(where);
    statement.append("Service = 0 ");
    statement.append(orderBy);
    statement.append("BikeId");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) {
            result.push_back(query->value(0).toString());
            result.push_back(query->value(1).toString());
        }
    }
    if (querySuccess && result[0] == NULL) result[0] = "None found";
    return result;
}

QVector<QString> Analyzer::DistanceBikesAbove5() {
    QVector<QString> result;
    QString statement = select2;
    statement.append(from);
    statement.append(where);
    statement.append("Health >= 5 ");
    statement.append(orderBy);
    statement.append("BikeId");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) {
            result.push_back(query->value(0).toString());
            result.push_back(query->value(1).toString());
        }
    }
    if (querySuccess && result[0] == NULL) result[0] = "None found";
    return result;
}

QVector<QString> Analyzer::DistanceBikesBelow5() {
    QVector<QString> result;
    QString statement = select2;
    statement.append(from);
    statement.append(where);
    statement.append("Health = 5 ");
    statement.append(orderBy);
    statement.append("BikeId");
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) {
            result.push_back(query->value(0).toString());
            result.push_back(query->value(1).toString());
        }
    }
    if (querySuccess && result[0] == NULL) result[0] = "None found";
    return result;
}
