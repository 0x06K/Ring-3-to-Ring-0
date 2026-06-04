@echo off
setlocal enabledelayedexpansion

echo Compiling all C files...
echo.

REM Create build folder if it doesn't exist
if not exist "build" mkdir build

REM Loop through all .c files in current directory
for %%f in (*.c) do (
    echo Compiling %%f...
    gcc "%%f" -o "build\%%~nf.exe"
    if !errorlevel! equ 0 (
        echo [SUCCESS] build\%%~nf.exe created
    ) else (
        echo [FAILED] %%f compilation failed
    )
    echo.
)

echo Done!
pause