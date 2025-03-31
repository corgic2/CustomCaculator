@ECHO OFF
set CURDIR=%~dp0
md build
cd build
cmake -DCMAKE_CONFIGURATION_TYPES=Release .. -G "Visual Studio 17 2022"
cmake --build . --config Release

@REM windeployqt
if defined QT_DIR (
    set QTDIR=%QT_DIR%
) else (
    set QTDIR=D:/Qt/5.15.2/msvc2019_64
)
cd %CURDIR%
set OUTPUTDIR=%~dp0\x64\Release
cd %OUTPUTDIR%
for /f %%I in ('dir /b *.exe *.dll') do (
    %QTDIR%\bin\windeployqt.exe --dir %OUTPUTDIR% --libdir %OUTPUTDIR% --plugindir %OUTPUTDIR% --no-translations %OUTPUTDIR%\%%~nxI
)
cd %CURDIR%
pause
