@echo off

if "%~1"=="" (
    echo Usage: build_obj filename.c
    exit /b 1
)

if not exist build (
    mkdir build
)

set SRC=%~1
set NAME=%~n1

gcc "%SRC%" -o ".\build\%NAME%.exe"

if %ERRORLEVEL%==0 (
    echo Built: build\%NAME%.exe
) else (
    echo Build failed.
)
