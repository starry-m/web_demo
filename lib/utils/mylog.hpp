#pragma once

#include <ctime>
#include <mutex>
#include <fstream>
#include <string>
#include <iostream>
#define FMT_HEADER_ONLY
#include <fmt/core.h>
#include <fmt/chrono.h>
#include <fmt/os.h>


class Logger {
public:
    // 默认不写入文件
    template <typename... Args>
    static void slog(const std::string& format, Args&&... args)
    {
        slogInternal(false, format, std::forward<Args>(args)...);
    }

    // 显式指定是否写入文件
    template <typename... Args>
    static void sflog( const std::string& format, Args&&... args)
    {
        slogInternal(true, format, std::forward<Args>(args)...);
    }

private:
    // 内部实现方法
    template <typename... Args>
    static void slogInternal(bool writeToFile, const std::string& format, Args&&... args)
    {
        // 获取当前时间
        std::time_t t = std::time(nullptr);
        auto formatted_time = fmt::format("{:%Y-%m-%d %H:%M:%S}", fmt::localtime(t));

        // 格式化输入的消息
        auto formatted_message = fmt::format(format, std::forward<Args>(args)...);

        // 打印带时间戳的日志
        fmt::print("[{}] {}\n", formatted_time, formatted_message);

        // 如果需要写入日志文件
        if (writeToFile) {
            std::lock_guard<std::mutex> lock(file_mutex); // 确保线程安全
//            auto log_file = fmt::output_file(getLogFileName());
//            log_file.print("[{}] {}\n", formatted_time, formatted_message);
            // 使用 std::ofstream 打开文件
            std::ofstream log_file(getLogFileName(), std::ios::app);
            if (log_file.is_open()) {
                log_file << "[" << formatted_time << "] " << formatted_message << std::endl;
            }
        }

    }

    // 获取当前日期的日志文件名（格式：log_YYYY-MM-DD.txt）
    static std::string getLogFileName()
    {
        auto now = std::chrono::system_clock::now();
        auto now_time_t = std::chrono::system_clock::to_time_t(now);
        return fmt::format("log_{:%Y-%m-%d}.txt", fmt::localtime(now_time_t));
    }

    static std::mutex file_mutex; // 静态互斥锁
};

// 静态成员初始化
std::mutex Logger::file_mutex;
