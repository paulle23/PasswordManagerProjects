To Run this file in powershell, navigate to project folder
0. if you added files, do cmake -S . -B build -G "MinGW Makefiles" -DQt6_DIR="C:\Qt\6.11.1\mingw_64\lib\cmake\Qt6" 
1. cmake --build build
2. .\build\PasswordManagerGUI.exe in terminal
if you only change existing files 
1. cmake --build build
2. .\build\PasswordManagerGUI.exe in terminal

C:\Qt\6.11.1\mingw_64\bin\windeployqt.exe build\PasswordManagerGUI.exe after editing to rebuild in powershell
Running it through VSCode
- uses CMake tools
1. Control Shift P
2. CMake: build
3. CMake: Run Without Debugging

Fix your CMake compiler

Delete your build folder:
    Remove-Item -Recurse -Force build
Then configure using Qt's MinGW compiler:
    cmake -S . -B build -G "MinGW Makefiles" `
    -DCMAKE_C_COMPILER="C:/Qt/Tools/mingw1310_64/bin/gcc.exe" `
    -DCMAKE_CXX_COMPILER="C:/Qt/Tools/mingw1310_64/bin/g++.exe" `
    -DQt6_DIR="C:/Qt/6.11.1/mingw_64/lib/cmake/Qt6"

Then:
    cmake --build build


Final?
    .\build\PasswordManagerGUI.exe
    echo $LASTEXITCODE
Also check if the executable still exists:
    dir .\build\PasswordManagerGUI.exe
If it returns -1073741515 again
That means missing Qt DLLs. Run:
    C:\Qt\6.11.1\mingw_64\bin\windeployqt.exe .\build\PasswordManagerGUI.exe
Then 
    .\build\PasswordManagerGUI.exe



Features
Uses Qt for frontend
SQLite database