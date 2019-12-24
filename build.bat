@echo off

if exist build (
  rmdir /s /q build
)

set BUILD_TYPE=Release
if "%1" == "" (
	set BUILD_TYPE=%1
)

mkdir build && cd build
cmake .. -D CMAKE_BUILD_TYPE=%BUILD_TYPE%
cmake --build .
cd ..