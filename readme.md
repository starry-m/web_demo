# cpp_cmake_template

work in linux platform,aims to cross paltform ,running in arm linux 
!
- 安装库
``` shell
//boost
sudo apt-get update
sudo apt-get install libboost-all-dev
// mqtt  :https://github.com/eclipse/paho.mqtt.cpp
$ git clone https://github.com/eclipse/paho.mqtt.cpp
$ cd paho.mqtt.cpp
$ git co v1.4.0
$ git submodule init
$ git submodule update

$ cmake -Bbuild -H. -DPAHO_WITH_MQTT_C=ON -DPAHO_BUILD_EXAMPLES=ON
$ sudo cmake --build build/ --target install

```
`注意，Mqtt的库都是动态库，因此需要交叉编译，部署到arm上`
``` shell
mkdir build && cd build
cmake ..
make 

```


测试成功！
交叉编译paho库步骤：
- 1.首先检查buidroot和系统上的版本是否一致,这里使用的是 paho.mqtt.cpp:1.2.0   paho.mqtt.c:1.3.13
- 2.参考https://blog.csdn.net/wkd_007/article/details/138805571
- 3.编译器:arm-rockchip830-linux-uclibcgnueabihf-gcc  arm-rockchip830-linux-uclibcgnueabihf-g++

- 4.注意 paho.mqtt.cpp_install.sh
- 5.cmake工程注意包含include目录和lib目录




## 开源库使用

- 日志 ：spdlog
- web: [mongoose](https://github.com/cesanta/mongoose)


## start!!!
将模板mongoose wizard  复制进工程


## 测试使用

```shell
Wrote timer to /sys/class/leds/beaglebone:green:usr0/trigger
Failed to open file: /sys/class/leds/beaglebone:green:usr0/delay_on
Failed to open file: /sys/class/leds/beaglebone:green:usr0/delay_off

```
出现写入权限不足的情况，加sudo执行即可

``` shell
terminate called after throwing an instance of 'std::system_error'   what():  Enable multithreading to use std::thread: Operation not permitted Aborted
```
出现多线程使用失败的情况，链接Threads就可以了
