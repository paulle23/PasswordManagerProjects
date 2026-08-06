#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>

class Database{
private:
    QSqlDatabase db;
public:
    Database();
    bool openDatabase();
    void createTables();
};
#endif