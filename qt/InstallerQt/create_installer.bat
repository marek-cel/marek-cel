set INSTALLER_NAME=testapp-1.0-win32

del %INSTALLER_NAME%.exe
del qti\%INSTALLER_NAME%.exe

set testapp_dir=qti\packages\pl.marekcel.testapp

copy /y bin\test.exe %testapp_dir%\data
copy /y src\test.ico %testapp_dir%\data

copy /y LICENSE.txt %testapp_dir%\meta

cd qti

C:\Qt\QtIFW-3.1.0\bin\binarycreator.exe -c config\config.xml -p packages %INSTALLER_NAME%.exe

move %INSTALLER_NAME%.exe ..\%INSTALLER_NAME%.exe

pause
