#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

class QLineEdit;
class QPushButton;

class LoginWindow : public QWidget{
    Q_OBJECT
private:
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QPushButton *showUsersButton;
public:
    LoginWindow();
private slots:
    void login();
    void openRegister();
    void showUsers();
};
#endif