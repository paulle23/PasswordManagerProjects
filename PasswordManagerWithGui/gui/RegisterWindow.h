#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>

class QLineEdit;
class QPushButton;

class RegisterWindow : public QWidget{
    Q_OBJECT
private:
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QLineEdit *confirmPasswordInput;
    QPushButton *registerButton;
public:
    RegisterWindow();
private slots:
    void registerUser();
private:
    QString passwordStrength(QString password);
};
#endif