@echo off
setlocal enabledelayedexpansion

:: Set variables
set BOOST_VERSION=1_82_0
set BOOST_DIR=%USERPROFILE%\boost
set BOOST_ROOT=%BOOST_DIR%\boost_%BOOST_VERSION%
set DOWNLOAD_URL=https://archives.boost.io/release/1.82.0/source/boost_%BOOST_VERSION%.zip
set TEMP_ZIP=%TEMP%\boost_%BOOST_VERSION%.zip
set SEVENZIP="C:\Program Files\7-Zip\7z.exe"

echo Starting Boost %BOOST_VERSION% installation...

:: Check if 7-Zip is installed
if not exist %SEVENZIP% (
    echo 7-Zip not found at %SEVENZIP%!
    echo Please install 7-Zip first.
    exit /b 1
)

:: Create boost directory if it doesn't exist
if not exist "%BOOST_DIR%" (
    echo Creating boost directory...
    mkdir "%BOOST_DIR%"
)

:: Download Boost
echo Downloading Boost from %DOWNLOAD_URL%...
powershell -Command "& {[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; Invoke-WebRequest -Uri '%DOWNLOAD_URL%' -OutFile '%TEMP_ZIP%'}"
if %ERRORLEVEL% NEQ 0 (
    echo Failed to download Boost!
    exit /b 1
)

:: Extract Boost using 7-Zip
echo Extracting Boost to %BOOST_DIR%...
%SEVENZIP% x "%TEMP_ZIP%" -o"%BOOST_DIR%" -y
if %ERRORLEVEL% NEQ 0 (
    echo Failed to extract Boost!
    del "%TEMP_ZIP%"
    exit /b 1
)

:: Clean up zip file
del "%TEMP_ZIP%"

:: Run bootstrap
echo Running bootstrap...
cd /d "%BOOST_ROOT%"
call bootstrap.bat
if %ERRORLEVEL% NEQ 0 (
    echo Bootstrap failed!
    exit /b 1
)

:: Run b2
echo Building Boost...
.\b2
if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    exit /b 1
)

:: Set environment variables
echo Setting environment variables...
setx BOOST_ROOT "%BOOST_ROOT%" /M
setx BOOST_LIBRARYDIR "%BOOST_ROOT%\stage\lib" /M

echo.
echo Boost %BOOST_VERSION% installation completed successfully!
echo.
echo Installation details:
echo - Boost root: %BOOST_ROOT%
echo - Library path: %BOOST_ROOT%\stage\lib
echo.
echo Please restart your command prompt for environment variables to take effect.

endlocal
pause
