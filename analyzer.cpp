#include "analyzer.h"
#include <QDebug>

Analyzer::Analyzer(QSqlQuery *a)
{
query = a;
}

QVector<QString> Analyzer::TotalBikesCheckedIn() {
    QVector<QString> result;
    QString statement = select1;
    statement.append(from);
    statement.append(where);
    statement.append("CheckedOut = 0");
    qDebug() << "Analyze statement: " <<statement;
    bool querySuccess = false;
    if (query->exec(statement)) {
        querySuccess = true;
        while(query->next()) {
            //qDebug() << query->value(0).toString();
            result.push_back(query->value(0).toString());
        }
    } else {
        qDebug() <<"Analyze failed!";
    }
    if (querySuccess && result.empty()) result.push_back( "None found");

    return result;
}

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

QVector<QString> Analyzer::DistanceBikesCheckedIn() {
    QVector<QString> result;
    QString statement = select2;
    statement.append(from);
    statement.append(where);
    statement.append("CheckedOut = 0");
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

QVector<QString> Analyzer::DistanceBikesBelow5() {
    QVector<QString> result;
    QString statement = select2;
    statement.append(from);
    statement.append(where);
    statement.append("Health = 5");
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
