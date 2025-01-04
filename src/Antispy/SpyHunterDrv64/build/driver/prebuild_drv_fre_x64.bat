@echo off

set project_name=UnknownProject
set target_os=win7
set target_ostag=W7

if "%1" == "" (
	echo "===> Project name empty"
	exit /b -1
) else (
	set project_name=%1
)

if "%2" == "" (
	echo "===> Targrt OS empty"
	exit /b -1
) else (
	set target_os=%2
)

set PWD=%~dp0
set DRV_NAME=%project_name%

if "%target_os%" == "win7" (
	set DEFAULT_OUTPUT_FOLDER=objfre_win7_amd64
	set target_ostag=W7
	set DDK_DIR=%W7BASE%
) else if "%target_os%" == "wlh" (
	set DEFAULT_OUTPUT_FOLDER=objfre_wlh_amd64
	set target_ostag=WLH
	set DDK_DIR=%WLHBASE%
) else (
	echo "===> Targrt OS invalid"
	exit /b -1
)

REM prepare build context environment!!
if NOT DEFINED DRV_PROJECT_ROOT SET DRV_PROJECT_ROOT=%PWD%..\..\SpyHunterDrv64\
if NOT DEFINED BUILD_OUTPUT_DIR SET BUILD_OUTPUT_DIR=%PWD%..\..\output\
SET DRIVER_ROOT=%BUILD_OUTPUT_DIR%amd64\%target_ostag%_Release
cd /D %DRV_PROJECT_ROOT%
call %DDK_DIR%\bin\setenv %DDK_DIR% fre x64 %target_os% no_oacr

REM build driver!!!
cd /D %DRV_PROJECT_ROOT%
IF EXIST %BUILD_OUTPUT_DIR% del /q %BUILD_OUTPUT_DIR%\*
IF EXIST .\%DEFAULT_OUTPUT_FOLDER%\amd64 del /q .\%DEFAULT_OUTPUT_FOLDER%\amd64\*
nmake

if NOT EXIST .\%DEFAULT_OUTPUT_FOLDER%\amd64\%DRV_NAME%.sys goto Done
%systemroot%\System32\xcopy .\%DEFAULT_OUTPUT_FOLDER%\amd64\%DRV_NAME%.sys /r /y %DRIVER_ROOT%\bin\
%systemroot%\System32\xcopy .\%DEFAULT_OUTPUT_FOLDER%\amd64\%DRV_NAME%.pdb /r /y %DRIVER_ROOT%\symbols\

:Done
rmdir /s /q %DRV_PROJECT_ROOT%%DEFAULT_OUTPUT_FOLDER%
cd %PWD%

@echo on
exit