编译 main.cpp
g++ -std=c++17 C:\String\CPPAPP\main.cpp -L"." -lCSharpStrLib -o C:\String\CPPAPP\main.exe
发布动态库
dotnet publish -p:NativeLib=Shared -r win-x64 -c Release