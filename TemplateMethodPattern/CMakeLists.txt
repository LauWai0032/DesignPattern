# 指定构建该项目所需的最低 CMake 版本，低于此版本的 CMake 会报错
# 这里要求 CMake 版本不低于 3.28.3，需与本地安装的 CMake 版本兼容
cmake_minimum_required(VERSION 3.28.3)

# 定义项目名称为 TemplateMethodPattern，同时会隐式设置 PROJECT_NAME 等相关变量
# 项目核心是实现 "模板方法模式"（设计模式），名称与设计模式主题对应
project(TemplateMethodPattern)

# 设置 C++ 标准为 C++20，启用 C++20 的特性（如概念、范围等）
# 确保项目代码能使用 C++20 语法和标准库功能，需编译器支持（如 GCC 10+、Clang 10+、MSVC 19.28+）
set(CMAKE_CXX_STANDARD 20)

# 设置可执行文件的输出目录：将编译生成的可执行文件放到项目根目录下的 bin 文件夹中
# PROJECT_SOURCE_DIR 是 CMake 内置变量，指向 CMakeLists.txt 所在的项目根目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 添加头文件搜索目录：让编译器能找到 include 文件夹下的头文件（.h/.hpp）
# 后续代码中可直接使用 #include "xxx.h" 包含该目录下的头文件，无需写相对路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 递归查找源文件：遍历 src 目录及其所有子目录下的所有 .cpp 文件
# LIST_DIRECTORIES false：仅查找文件，不包含目录（避免误将目录当作源文件）
# CMAKE_CURRENT_SOURCE_DIR：当前 CMakeLists.txt 所在的目录（此处即项目根目录）
# SRC_FILES：自定义变量，存储找到的所有源文件路径列表
file(GLOB_RECURSE SRC_FILES LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# 生成可执行文件：指定可执行文件名称为 TemplateMethodPattern（与项目名一致）
# 依赖的源文件为 SRC_FILES 变量中存储的所有 .cpp 文件
add_executable(TemplateMethodPattern ${SRC_FILES})