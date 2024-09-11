# CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(MString)

# 包含头文件目录
include_directories(${PROJECT_BINARY_DIR}/../include)

# 源文件列表
aux_source_directory(${PROJECT_BINARY_DIR}/../src SRC_LIST)
aux_source_directory(${PROJECT_BINARY_DIR}/../test TEST_SRC)

# 查找库文件
find_library(FUNC_LIB CSharpStrLib ${PROJECT_BINARY_DIR}/../lib)

# 设置可执行文件生成位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

# 生成可执行文件
add_executable(main ${TEST_SRC} ${SRC_LIST})

# 下面只是记录一下
# # 生成动态库
# # 参数 1：库名称，参数 2：库类型，参数 3：生成所需源文件列表
# add_library(func_shared SHARED ${PROJECT_BINARY_DIR}/../CSharpStrLib/string.cs)

# # 设置最终生成库名称
# set_target_properties(func_shared PROPERTIES OUTPUT_NAME "CSharpStrLib")

# 链接外部库（如果有）
target_link_libraries(main ${FUNC_LIB})

# 在CMake 中增加编译选项
add_compile_options(-std=c++17)