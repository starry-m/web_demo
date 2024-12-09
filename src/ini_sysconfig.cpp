//
// Created by starry on 24-12-9.
//
#include "simpleini/SimpleIni.h"
#include <iostream>
#include "utils/mylog.hpp"

//#define FMT_HEADER_ONLY
//
//#include "fmt/core.h"
//#include <fmt/chrono.h>

#define INI_FILE_PATH  "../conf.ini"
using namespace std;

void sysConfigInit(void)
{
    CSimpleIniA ini;
    ini.SetUnicode();
    SI_Error rc = ini.LoadFile(INI_FILE_PATH);
    if (rc < 0) { /* handle error */ };

    const char* pv;
//    pv = ini.GetValue("section", "key", "default");
//    ini.SetValue("section", "key", "7");
    pv = ini.GetValue("hal", "led_path");
    Logger::slog("The value of pv is: {}", string(pv));  // 使用 std::string
    // 获取当前时间
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now); // 转换为 time_t
    auto now_tm = *std::localtime(&now_time_t);                 // 转换为 tm
    // 使用 fmt 格式化日期和时间
    ini.SetValue("hal", "date", fmt::format("{:%Y-%m-%d}", now_tm).c_str());
    ini.SetValue("hal", "time", fmt::format("{:%H:%M:%S}", now_tm).c_str());

    rc = ini.SaveFile(INI_FILE_PATH);
    if (rc < 0) {
        Logger::slog("保存{}ini文件失败",INI_FILE_PATH);
    }
    Logger::slog("Simple log message.");
    Logger::sflog("start form here.Value = {}, Text = '{}',Floating point = {:.2f}",12,"example",3.14159);
}
