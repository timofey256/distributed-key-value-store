@echo off
setlocal enabledelayedexpansion

echo This script will install Boost libraries required for the distributed-kv-store project
echo This requires vcpkg and will take some time to complete.
set /p PROCEED=Do you want to proceed with the installation? (Y/N): 

if /i "%PROCEED%"=="Y" (
    echo Checking if vcpkg is installed...
    
    if exist "%USERPROFILE%\vcpkg\vcpkg.exe" (
        set VCPKG_PATH=%USERPROFILE%\vcpkg
    ) else if exist "C:\vcpkg\vcpkg.exe" (
        set VCPKG_PATH=C:\vcpkg
    ) else (
        echo vcpkg not found. Installing vcpkg...
        
        :: Create temporary directory
        set TEMP_DIR=%TEMP%\vcpkg_install
        mkdir "%TEMP_DIR%" 2>nul
        cd "%TEMP_DIR%"
        
        :: Clone vcpkg
        echo Cloning vcpkg repository...
        git clone https://github.com/Microsoft/vcpkg.git
        if errorlevel 1 (
            echo Error: Git clone failed. Please install Git and try again.
            exit /b 1
        )
        
        :: Bootstrap vcpkg
        cd vcpkg
        call bootstrap-vcpkg.bat
        if errorlevel 1 (
            echo Error: vcpkg bootstrap failed.
            exit /b 1
        )
        
        :: Move vcpkg to permanent location
        echo Moving vcpkg to %USERPROFILE%\vcpkg
        xcopy /E /I /H /R /Y . "%USERPROFILE%\vcpkg\"
        cd ..
        rd /s /q vcpkg
        set VCPKG_PATH=%USERPROFILE%\vcpkg
    )
    
    echo Installing Boost using vcpkg...
    "%VCPKG_PATH%\vcpkg" install boost:x64-windows
    if errorlevel 1 (
        echo Error: Boost installation failed.
        exit /b 1
    )
    
    echo Integrating with Visual Studio...
    "%VCPKG_PATH%\vcpkg" integrate install
    if errorlevel 1 (
        echo Error: Visual Studio integration failed.
        exit /b 1
    )
    
    echo Installation completed!
) else (
    echo Installation cancelled.
)

endlocal