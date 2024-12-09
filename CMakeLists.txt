cmake_minimum_required(VERSION 3.7.4)

# 设置默认构建类型为 Release
# if(NOT CMAKE_BUILD_TYPE)
#     set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type (Release, Debug, etc.)" FORCE)
# endif()

project(web_demo)
message(STATUS "CMake system name: " ${CMAKE_SYSTEM_NAME})
message(STATUS "CMake system processor: " ${CMAKE_SYSTEM_PROCESSOR})

set(CMAKE_CXX_STANDARD 14)  # C++14
set(CMAKE_C_STANDARD 11)     # C11
# 打印 C 和 C++ 的版本
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "C Standard: ${CMAKE_C_STANDARD}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
# 设置可执行文件输出路径 PROJECT_BINARY_DIR
# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

file(GLOB_RECURSE SRC_DIR_LIST "src/*.cpp" "src/*.c")	#遍历获取source/路径下所有的*.cpp和*.c文件列表

aux_source_directory(lib   lib_LIST)
set(ini  ${CMAKE_SOURCE_DIR}/lib/inih/ini.c ${CMAKE_SOURCE_DIR}/lib/inih/cpp/INIReader.cpp)
add_compile_options(-O2)

add_executable(${PROJECT_NAME} ${SRC_DIR_LIST} ${lib_LIST} ${ini})

target_include_directories(${PROJECT_NAME} PUBLIC include src)
target_include_directories(${PROJECT_NAME} PUBLIC lib)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/inih ${CMAKE_SOURCE_DIR}/lib/inih/cpp)


# add_subdirectory (glog )

# message(STATUS "Found glog version: ${glog_VERSION}")
# target_link_libraries(${PROJECT_NAME} glog)
# 如果目标架构是 ARM，则添加库目录和链接库
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")
    message(STATUS "Target processor is ARM, linking ARM-specific libraries.")
   
else()
    message(STATUS "Target processor is not ARM, skipping ARM-specific libraries.")
    

    # if(glog_FOUND)
    #      message(STATUS "Found glog version: ${glog_VERSION}")
    # endif()

endif()



set(CMAKE_EXPORT_COMPILE_COMMANDS ON)