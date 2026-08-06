#include "RegisterWindow.h"

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

#include <QSqlQuery>
#include <QSqlError>

#include <QRegularExpression>

RegisterWindow::RegisterWindow(){
    setWindowTitle("Create Account");
    setFixedSize(350,300);

    QLabel *title = new QLabel("Register New User");

    usernameInput = new QLineEdit();

    usernameInput->setPlaceholderText(
                "Username"
                );

    passwordInput = new QLineEdit();

    passwordInput->setPlaceholderText(
                "Password"
                );

    passwordInput->setEchoMode(QLineEdit::Password);

    confirmPasswordInput = new QLineEdit();

    confirmPasswordInput->setPlaceholderText(
                "Confirm Password"
                );
    confirmPasswordInput->setEchoMode(QLineEdit::Password);

    registerButton =
            new QPushButton(
                "Register"
                );

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(title);
    layout->addWidget(usernameInput);
    layout->addWidget(passwordInput);
    layout->addWidget(confirmPasswordInput);
    layout->addWidget(registerButton);

    setLayout(layout);

    connect(registerButton,
            &QPushButton::clicked,
            this,
            &RegisterWindow::registerUser);
}

QString RegisterWindow::passwordStrength(QString password){
    bool upper=false;
    bool lower=false;
    bool digit=false;
    bool special=false;

    QString specials = "!@#$%^&*()-+";
    for(QChar c : password){
        if(c.isUpper())
            upper=true;
        else if(c.isLower())
            lower=true;
        else if(c.isDigit())
            digit=true;
        else if(specials.contains(c))
            special=true;
    }
    int score =
            upper+
            lower+
            digit+
            special+
            (password.length()>=8);

    if(score==5)
        return "Strong";
    if(score>=3)
        return "Medium";
    return "Weak";
}

void RegisterWindow::registerUser(){
    QString username = usernameInput->text();
    QString password = passwordInput->text();
    QString confirm = confirmPasswordInput->text();

    if(username.isEmpty() || password.isEmpty()){
        QMessageBox::warning(
                    this,
                    "Error",
                    "Fill all fields"
                    );
        return;
    }

    if(password != confirm){
        QMessageBox::warning(
                    this,
                    "Error",
                    "Passwords do not match"
                    );
        return;
    }

    QString strength = passwordStrength(password);

    if(strength=="Weak"){
        QMessageBox::warning(
                    this,
                    "Weak Password",
                    "Password must contain:\n"
                    "- 8 characters\n"
                    "- Uppercase\n"
                    "- Lowercase\n"
                    "- Number\n"
                    "- Special character"
                    );
        return;
    }

    QSqlQuery check;

    check.prepare(
    "SELECT username FROM users "
    "WHERE username=?"
    );

    check.addBindValue(username);

    if(check.exec() && check.next()){
        QMessageBox::warning(
                    this,
                    "Error",
                    "Username already exists"
                    );
        return;
    }

    QSqlQuery query;
    query.prepare(
    "INSERT INTO users(username,password)"
    "VALUES(?,?)"
    );

    query.addBindValue(username);
    query.addBindValue(password);

    if(query.exec()){
        QMessageBox::information(
                    this,
                    "Success",
                    "Account created!"
                    );
        close();
    }
    else{
        QMessageBox::critical(
                    this,
                    "Database Error",
                    query.lastError().text()
                    );
    }
}