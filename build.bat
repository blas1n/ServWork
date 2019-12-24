@echo off

if exist build (
  rd /s /q build
)

mkdir build && cd build
cmake .. || goto :error
make || goto :error
cd ..

:error
cd ..
echo Failed build with error #%errorlevel%
exit /b %errorlevel% 