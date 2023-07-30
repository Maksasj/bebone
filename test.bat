@ECHO OFF

cmake --build build

cd build\tests\
ctest
cd ..\..