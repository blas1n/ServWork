@echo off

if exist build (
  rd /s /q build
)

set build=Release
if "%1" == "" (
	set build=%1
)

mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=%build% .. || goto :error
make run || goto :error
cd ..

:error
cd ..
echo Failed build with error #%errorlevel%
exit /b 1