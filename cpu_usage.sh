#!/bin/bash

# 获取 CPU 使用率
cpu_usage=$(top -bn1 | grep "Cpu(s)" | awk '{print $2}')

# 获取内存使用量
mem_usage=$(free -m | awk '/^Mem/ {printf "%.2f", $3/$2 * 100.0}')

echo "CPU 使用率: $cpu_usage%"
echo "内存使用率: $mem_usage%"

