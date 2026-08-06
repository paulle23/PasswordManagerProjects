#include "LoginWindow.h"

#include "RegisterWindow.h"
#include "MainWindow.h"

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

#include <QSqlQuery>
#include <QSqlError>

LoginWindow::LoginWindow(){//constructor
    setWindowTitle("Password Manager Login");
    setFixedSize(350,250);

    QLabel *title = new QLabel("Password Manager");//create title
    usernameInput = new QLineEdit();
    usernameInput->setPlaceholderText("Username");

    passwordInput = new QLineEdit();
    passwordInput->setPlaceholderText("Password");
    passwordInput->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton("Login");
    registerButton = new QPushButton("Register");
    showUsersButton = new QPushButton("Show Registered Users");
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(title);
    layout->addWidget(usernameInput);
    layout->addWidget(passwordInput);
    layout->addWidget(loginButton);
    layout->addWidget(registerButton);
    layout->addWidget(showUsersButton);

    setLayout(layout);

    connect(loginButton,
            &QPushButton::clicked,
            this,
            &LoginWindow::login);

    connect(registerButton,
            &QPushButton::clicked,
            this,
            &LoginWindow::openRegister);
    connect(showUsersButton,
        &QPushButton::clicked,
        this,
        &LoginWindow::showUsers);
}

void LoginWindow::login(){//verifies credentials
    QString username = usernameInput->text();
    QString password = passwordInput->text();

    QSqlQuery query;

    query.prepare(
    "SELECT * FROM users "
    "WHERE username=? "
    "AND password=?"
    );

    query.addBindValue(username);
    query.addBindValue(password);

    if(query.exec() && query.next()){
        QMessageBox::information(
                    this,
                    "Success",
                    "Login successful!"
                    );

        MainWindow *main = new MainWindow(username);

        main->show();
        this->close();
    }
    else{
        QMessageBox::warning(
                    this,
                    "Error",
                    "Invalid username or password"
                    );
    }
}

void LoginWindow::openRegister(){
    RegisterWindow *registerWindow = new RegisterWindow();
    registerWindow->show();
}

void LoginWindow::showUsers(){
    QSqlQuery query;

    if(query.exec("SELECT username FROM users")){
        QString users = "Registered Users:\n\n";

        while(query.next()){
            users += query.value(0).toString();
            users += "\n";
        }

        QMessageBox::information(
            this,
            "Users",
            users
        );
    }
    else{
        QMessageBox::warning(
            this,
            "Database Error",
            query.lastError().text()
        );
    }
}