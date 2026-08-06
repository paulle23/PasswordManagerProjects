#include "MainWindow.h"

#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QInputDialog>
#include <QMessageBox>

#include <QSqlQuery>
#include <QSqlError>

MainWindow::MainWindow(QString user){
    currentUser=user;

    setWindowTitle("Password Manager - " + currentUser);
    resize(700,450);

    table = new QTableWidget();
    table->setColumnCount(3);

    QStringList headers;
    headers << "Account" << "Username" << "Password";
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setStretchLastSection(true);

    searchInput = new QLineEdit();
    searchInput->setPlaceholderText("Search account...");

    addButton = new QPushButton("Add");
    deleteButton = new QPushButton("Delete");
    updateButton = new QPushButton("Update");
    showButton = new QPushButton("Show Password");
    searchButton = new QPushButton("Search");
    logoutButton = new QPushButton("Logout");

    QHBoxLayout *buttons = new QHBoxLayout();

    buttons->addWidget(searchInput);
    buttons->addWidget(searchButton);
    buttons->addWidget(addButton);
    buttons->addWidget(deleteButton);
    buttons->addWidget(updateButton);
    buttons->addWidget(showButton);
    buttons->addWidget(logoutButton);

    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(table);
    layout->addLayout(buttons);
    setLayout(layout);

    connect(addButton,
            &QPushButton::clicked,
            this,
            &MainWindow::addPassword);

    connect(deleteButton,
            &QPushButton::clicked,
            this,
            &MainWindow::deletePassword);

    connect(updateButton,
        &QPushButton::clicked,
        this,
        &MainWindow::updatePassword);

    connect(showButton,
        &QPushButton::clicked,
        this,
        &MainWindow::showPasswords);

    connect(searchButton,
            &QPushButton::clicked,
            this,
            &MainWindow::searchPassword);

    connect(logoutButton,
            &QPushButton::clicked,
            this,
            &MainWindow::logout);
    loadPasswords();
}

void MainWindow::loadPasswords(){
    table->setRowCount(0);
    QSqlQuery query;
    query.prepare(
    "SELECT account,username,password "
    "FROM accounts "
    "WHERE owner=?"
    );
    query.addBindValue(currentUser);

    if(query.exec()){
        while(query.next()){
            int row = table->rowCount();
            table->insertRow(row);
            table->setItem(
                row,
                0,
                new QTableWidgetItem(
                    query.value(0).toString()
                )
            );
            table->setItem(
                row,
                1,
                new QTableWidgetItem(
                    query.value(1).toString()
                )
            );
            table->setItem(
                row,
                2,
                new QTableWidgetItem(
                    query.value(2).toString()
                )
            );
        }
    }
}

void MainWindow::addPassword(){
    bool ok;
    QString account =
        QInputDialog::getText(
            this,
            "Account",
            "Account name:",
            QLineEdit::Normal,
            "",
            &ok
        );

    if(!ok)
        return;

    QString username =
        QInputDialog::getText(
            this,
            "Username",
            "Username:",
            QLineEdit::Normal,
            "",
            &ok
        );

    if(!ok)
        return;

    QString password =
        QInputDialog::getText(
            this,
            "Password",
            "Password:",
            QLineEdit::Password,
            "",
            &ok
        );

    if(!ok)
        return;
    QSqlQuery query;

    query.prepare(
    "INSERT INTO accounts"
    "(owner,account,username,password)"
    "VALUES(?,?,?,?)"
    );

    query.addBindValue(currentUser);
    query.addBindValue(account);
    query.addBindValue(username);
    query.addBindValue(password);

    if(query.exec()){
        loadPasswords();
    }
    else{
        QMessageBox::warning(
            this,
            "Error",
            query.lastError().text()
        );
    }
}

void MainWindow::deletePassword(){
    int row = table->currentRow();

    if(row < 0)
        return;

    QString username =
        table->item(row,1)
             ->text();

    QSqlQuery query;

    query.prepare(
    "DELETE FROM accounts "
    "WHERE owner=? "
    "AND username=?"
    );

    query.addBindValue(currentUser);
    query.addBindValue(username);
    query.exec();

    loadPasswords();
}

void MainWindow::searchPassword(){
    QString text = searchInput->text();
    for(int i=0; i<table->rowCount(); i++){
        bool match =
        table->item(i,0)
             ->text()
             .contains(
                 text,
                 Qt::CaseInsensitive
             );

        table->setRowHidden(
            i,
            !match
        );
    }
}

void MainWindow::logout(){
    close();
}

void MainWindow::updatePassword(){
    int row = table->currentRow();
    if(row < 0)
        return;

    QString username = table->item(row,1)->text();
    bool ok;
    QString newPassword =
        QInputDialog::getText(
            this,
            "Update Password",
            "New password:",
            QLineEdit::Password,
            "",
            &ok
        );

    if(!ok)
        return;

    QSqlQuery query;

    query.prepare(
    "UPDATE accounts "
    "SET password=? "
    "WHERE owner=? "
    "AND username=?"
    );

    query.addBindValue(newPassword);
    query.addBindValue(currentUser);
    query.addBindValue(username);
    query.exec();

    loadPasswords();
}

void MainWindow::showPasswords(){
    passwordVisible = !passwordVisible;
    QSqlQuery query;

    query.prepare(
    "SELECT username,password "
    "FROM accounts "
    "WHERE owner=?"
    );

    query.addBindValue(currentUser);

    if(query.exec()){
        int row=0;

        while(query.next()){
            if(passwordVisible){
                table->item(row,2)
                ->setText(
                    query.value(1)
                         .toString()
                );
            }
            else{
                table->item(row,2)
                ->setText(
                    "********"
                );
            }
            row++;
        }
    }
}