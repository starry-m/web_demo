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
if [ "$USE_CROSS_COMPILE" == true ]; then
    rm -rf build
fi
# 保存当前路径
ROOTPATH=`pwd`

# rm -rf build

# 检查并创建 build 目录
if [ ! -d "$ROOTPATH/build" ]; then
    mkdir "$ROOTPATH/build"
fi

# 进入 build 目录
cd "$ROOTPATH/build"
# 检查并创建 build 目录
if [ ! -d "$ROOTPATH/build/log" ]; then
    mkdir "$ROOTPATH/build/log"
fi
# 运行 cmake
# cmake -DCMAKE_TOOLCHAIN_FILE=./toolchain.cmake  ..
# cmake ..


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
    # echo -e "Build completed successfully!\n"
fi
