# CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(MString)

# # 设置 C++ 标准
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(${PROJECT_BINARY_DIR}/../include)

# 源文件列表
aux_source_directory(${PROJECT_BINARY_DIR}/../src SRC_LIST)
aux_source_directory(${PROJECT_BINARY_DIR}/../main_src MAIN_SRC)

# 查找库文件
find_library(FUNC_LIB CSharpStrLib ${PROJECT_BINARY_DIR}/../lib)

# 设置可执行文件生成位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

# 生成可执行文件
add_executable(main ${MAIN_SRC} ${SRC_LIST})

# 链接外部库（如果有）
target_link_libraries(main ${FUNC_LIB})

# 在CMake 中增加编译选项
add_compile_options(-std=c++17)