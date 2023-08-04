@ECHO OFF

cmake --build build

cd build\tests\unit\
ctest
cd ..\..\..