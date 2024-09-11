# CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(MString)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(${PROJECT_BINARY_DIR}/../include)

# 源文件列表
aux_source_directory(${PROJECT_BINARY_DIR}/../src SRC_LIST)

# 添加可执行文件
add_executable(main ${SOURCES})

# 链接外部库（如果有）
# target_link_libraries(main CSharpStrLib)