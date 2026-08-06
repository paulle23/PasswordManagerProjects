#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QString>

class QTableWidget;
class QPushButton;
class QLineEdit;

class MainWindow : public QWidget{
    Q_OBJECT
private:
    QString currentUser;

    QTableWidget *table;

    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *updateButton;
    QPushButton *searchButton;
    QPushButton *showButton;
    QPushButton *logoutButton;

    QLineEdit *searchInput;
    bool passwordVisible = false;
public:
    MainWindow(QString user);
private slots:
    void loadPasswords();
    void addPassword();
    void deletePassword();
    void updatePassword();
    void searchPassword();
    void showPasswords();
    void logout();
};
#endif