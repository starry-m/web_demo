#!/bin/bash
# 检查是否使用交叉编译工具链
USE_CROSS_COMPILE=false
for arg in "$@"
do
    if [ "$arg" == "--cross" ]; then
        USE_CROSS_COMPILE=true
        break
    fi
done

# 设置构建目录，根据是否使用交叉编译选择不同目录
if [ "$USE_CROSS_COMPILE" == true ]; then
    BUILD_DIR="build_arm"
else
    BUILD_DIR="build"
fi

# 保存当前路径
ROOTPATH=`pwd`

# 如果是交叉编译，则删除 build_arm 目录
#if [ "$USE_CROSS_COMPILE" == true ]; then
#    rm -rf "$ROOTPATH/$BUILD_DIR"
#fi

# 检查并创建构建目录
if [ ! -d "$ROOTPATH/$BUILD_DIR" ]; then
    mkdir "$ROOTPATH/$BUILD_DIR"
fi

# 进入构建目录
cd "$ROOTPATH/$BUILD_DIR"

# 检查并创建 log 目录
if [ ! -d "$ROOTPATH/$BUILD_DIR/log" ]; then
    mkdir "$ROOTPATH/$BUILD_DIR/log"
fi

# 运行 cmake，根据是否使用交叉编译来选择参数
if [ "$USE_CROSS_COMPILE" == true ]; then
    cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake ..
else
    cmake ..
fi

# 检查 cmake 是否成功
if [ $? -ne 0 ]; then
    echo "CMake configuration failed!"
    exit 1
fi

# 运行 make
make

# 检查 make 是否成功
if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo -e "Build completed successfully!\n"

# 打印可执行文件的大小
EXECUTABLE="./web_demo"
if [ -f "$EXECUTABLE" ]; then
    echo "Executable file size:"
    ls -lh "$EXECUTABLE" | awk '{print $9 ": " $5}'
else
    echo "Executable file not found!"
fi

# 运行生成的可执行文件（仅在非交叉编译情况下）
if [ "$USE_CROSS_COMPILE" == false ]; then
    ./web_demo
fi
