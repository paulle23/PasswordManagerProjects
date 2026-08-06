cmake_minimum_required(VERSION 3.16)

project(PasswordManagerGUI)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS 
    Widgets
    Sql
)

add_executable(
    PasswordManagerGUI

    main.cpp

    database/Database.cpp
    database/Database.h
    database/Validator.h

    models/User.h

    gui/LoginWindow.cpp
    gui/LoginWindow.h

    gui/RegisterWindow.cpp
    gui/RegisterWindow.h

    gui/MainWindow.cpp
    gui/MainWindow.h
)

target_link_libraries(
    PasswordManagerGUI
    Qt6::Widgets
    Qt6::Sql
)