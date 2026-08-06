#include "Database.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
/*Connect to an SQLite database
Create the required database tables if they don't already exist*/
Database::Database(){ }//constructor

bool Database::openDatabase(){//attempts to connect to the database
    db = QSqlDatabase::addDatabase("QSQLITE");//create and store database connection in db
    db.setDatabaseName("passwordmanager.db");//specify the file

    if(!db.open()){
        qDebug() << "Database failed:" << db.lastError().text();
        return false;
    }
    return true;
}

void Database::createTables(){//creates tables if they dont already exist
    QSqlQuery query;//used to send SQL commands to the database

    query.exec(//SQL statement
    "CREATE TABLE IF NOT EXISTS users("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "username TEXT UNIQUE,"
    "password TEXT)"
    );

    query.exec(
    "CREATE TABLE IF NOT EXISTS accounts("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "owner TEXT,"
    "account TEXT,"
    "username TEXT,"
    "password TEXT)"
    );
}