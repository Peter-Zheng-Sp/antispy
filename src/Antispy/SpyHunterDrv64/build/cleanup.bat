@echo off

set PWD=%~dp0
set BUILD_OUTPUT_DIR=%PWD%\..\output

REM Delete files under output folder
del /F /A /S /Q "%BUILD_OUTPUT_DIR%"
pushd "%BUILD_OUTPUT_DIR%"
rd /S /Q ".\*"
popd
rd /S /Q "%BUILD_OUTPUT_DIR%"

@echo on
