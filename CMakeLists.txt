cmake_minimum_required(VERSION 3.0)
project(main)

#配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

#配置头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db/)
include_directories(${PROJECT_SOURCE_DIR}/include/server/model/)
include_directories(${PROJECT_SOURCE_DIR}/include/server/redis/)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)
#配置库文件搜索路径
#link_directories()

#设置可执行文件的生成路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#把.指定路径下的所有源文件名字放入变量名SRC_LIST中
#aux_source_directory(. SRC_LIST)

#加载子目录
add_subdirectory(src)

