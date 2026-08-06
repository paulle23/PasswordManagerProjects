#include <QApplication>

#include "database/Database.h"
#include "gui/LoginWindow.h"

/*Initializes the Qt framework.
Opens the application's database.
Creates required database tables.
Creates and displays the login window.
Starts Qt's event loop so the application remains responsive until it is closed.*/
int main(int argc, char *argv[]){
    QApplication app(argc, argv);//creates Qt application object to create GUI window

    Database database;//create database object

    if(!database.openDatabase()){//attempt to open database
        return -1;
    }
    database.createTables();//create database tables
    LoginWindow window;//create instance of login window
    window.show();//display the window
    return app.exec();//start the Qt event loop, which waits for and processes events like clicks
}