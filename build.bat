@echo off

if exist build (
  rd /s /q build
)

set BUILD_TYPE=Release
if "%1" == "" (
	set BUILD_TYPE=%1
)

mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=%BUILD_TYPE% .. || goto :error
make || mingw32-make || goto :error
cd ..

:error
cd ..
echo Failed build with error #%errorlevel%
exit /b 1