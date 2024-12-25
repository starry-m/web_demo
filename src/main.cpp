#include "hal.h"
#include "mongoose_glue.h"
#include <thread>
#include <array>
#include <cstdio>
#include <iostream>
#include "mymain.h"
#include "LED.h"

using namespace std;
static void blink_timer(void *arg) {
  (void) arg;
}

// 创建 LED 对象并存入容器
std::array<LED, 4> leds = {LED(0), LED(1), LED(2), LED(3)};

#if defined(__cplusplus)
extern "C" {
#endif
void update_led_status(int number,bool sate,int mode,int blink_delay_on,int blink_delay_off)
{
    if (number >= 0 && number < leds.size()) {
        std::cout <<"---------------chang led status:"<<number<< std::endl;
        leds[number].change_mode_status(sate, mode, blink_delay_on, blink_delay_off);
    } else {
        std::cout << "Invalid LED number: " << number << std::endl;
    }
}
#if defined(__cplusplus)
}
#endif

void web_thread()
{
    mg_log_set(MG_LL_INFO);
    MG_INFO(("HAL initialised, starting firmware..."));
    //http://127.0.0.1:8080/  HTTP_URL "http://0.0.0.0:8080"
    // This blocks forever. Call it at the end of main(), or in a
    // separate RTOS task. Give that task 8k stack space.
    mongoose_init();
    mg_timer_add(&g_mgr, 1000, MG_TIMER_REPEAT, blink_timer, NULL);
    for (;;) {
        mongoose_poll();
    }
}

std::string execCommand(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }
    pclose(pipe);
    return result;
}
extern struct state s_state;

void update_cpu_mem_usage()
{
    while(true)
    {
        // 执行命令并获取 CPU 和内存使用率（作为字符串）
        std::string cpuUsageStr = execCommand("top -bn1 | grep 'Cpu(s)' | awk '{print $2}'");
        std::string memUsageStr = execCommand("free -m | awk '/^Mem/ {print $3/$2 * 100.0}'");

        // 将字符串转为整数
        int cpuUsage = static_cast<int>(std::stof(cpuUsageStr));  // 转换为 float 再转为 int
        int memUsage = static_cast<int>(std::stof(memUsageStr));  // 转换为 float 再转为 int

        // 打印结果
//        std::cout << "CPU 使用率: " << cpuUsage << "%" << std::endl;
//        std::cout << "内存使用率: " << memUsage << "%" << std::endl;
        s_state.cpu=cpuUsage;
        s_state.mem=memUsage;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

}



int main(int argc, char* argv[]) {
//    sysConfigInit();
  // Cross-platform hardware init
    hal_init();
    std::thread mongoose_thread(web_thread);
    std::thread usage_thread(update_cpu_mem_usage);
    mongoose_thread.join();
    usage_thread.join();
    return 0;
}