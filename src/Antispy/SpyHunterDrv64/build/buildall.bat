@echo off

set target_os=win7
set chk_fre=chk
set project_name=SpyHunterDrv64
set PWD=%~dp0

if "%1"=="" (
	echo "===> Project name empty"
	exit /b -1
) else (
	set project_name=%1
)

if not "%2"=="" set target_os=%2
if not "%3"=="" set chk_fre=%3

echo "===> Build amd64 driver [%project_name%]"
if "%chk_fre%"=="chk" (
	echo "===> Mode: Debug"
	start /B /wait /i %PWD%\driver\prebuild_drv_chk_x64.bat %project_name% %target_os%
) else if "%chk_fre%"=="fre" (
	echo "===> Mode: Release"
	start /B /wait /i %PWD%\driver\prebuild_drv_fre_x64.bat %project_name% %target_os%
) else (
	echo "===> Mode Error"
	exit /b -1
)

REM Clear %ERRORLEVEL% to prevent fail
dir > nul

@echo on
