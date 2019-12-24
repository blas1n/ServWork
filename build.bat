@echo off

if exist build (
  rd /s /q build
)

mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. || goto :error
make || goto :error
cd ..

:error
cd ..
echo Failed build with error #%errorlevel%
exit /b %errorlevel% 