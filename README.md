# 编译 main.cpp
利用 cmake 构建
# C# 发布动态库
cd CSharpStrLib
dotnet publish -p:NativeLib=Shared -r win-x64 -c Release
# 测试单个测试文件
cd bin
./main.exe --gtest_filter="string.encoding"