#pragma once
//mylog.hpp
#include <iostream>
#include <mutex>
#include <atomic>
#include <fstream>
#include <sstream>
#include <thread>
#include <string>
#include <chrono>
#include <iomanip>

#define FMT_HEADER_ONLY

#include "fmt/core.h"
#include <fmt/chrono.h>

class Logger
{
public:
    // 打印带时间戳的消息
    static void log(const std::string &message)
    {
        std::string timestamp = getCurrentTime();
        std::cout << timestamp << " [Thread ID: " << std::this_thread::get_id() << "] -> " << message << std::endl;
    }
    // 打印带时间戳的消息 保存文件
    static void log(const std::string &message,std::mutex file_mutex)
    {
        std::string timestamp = getCurrentTime();
        std::cout << timestamp << " [Thread ID: " << std::this_thread::get_id() << "] -> " << message << std::endl;
        // 输出到日志文件
        std::lock_guard<std::mutex> lock(file_mutex);  // 保护文件写入
        std::ofstream log_file(getLogFileName(), std::ios::app); // 打开文件进行追加
        if (log_file.is_open())
        {
            log_file << timestamp << " [Thread ID: " << std::this_thread::get_id() << "] -> " << message << std::endl;
        }
    }
    template <typename... Args>
    static void slog(const std::string& format, Args&&... args)
    {
        // 获取当前时间
        std::time_t t = std::time(nullptr);
        auto formatted_time = fmt::format("{:%Y-%m-%d %H:%M:%S}", fmt::localtime(t));

        // 格式化输入的消息
        auto formatted_message = fmt::format(format, std::forward<Args>(args)...);

        // 打印带时间戳的日志
        fmt::print("[{}] {}\n", formatted_time, formatted_message);
    }


private:
    // 获取当前的时间戳（格式：YYYY-MM-DD HH:MM:SS）
    static std::string getCurrentTime()
    {
        // 获取当前系统时间
        auto now = std::chrono::system_clock::now();
        auto now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&now_time_t);

        // 格式化为 "YYYY-MM-DD HH:MM:SS"
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
    // 获取当前日期的日志文件名（格式：log_YYYY-MM-DD.txt）
    static std::string getLogFileName()
    {
        auto now = std::chrono::system_clock::now();
        auto now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&now_time_t);

        std::ostringstream oss;
        oss << "log_" << std::put_time(&tm, "%Y-%m-%d") << ".txt";
        return oss.str();
    }
};