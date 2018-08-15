#ifndef __ASSISTANCE_H__				// 如果没有定义__ASSISTANCE_H__
#define __ASSISTANCE_H__				// 那么定义__ASSISTANCE_H__

// ANSI C++标准库头文件
#include <cstring>					// 标准串操作
#include <iostream>					// 标准流操作
#include <limits>					// 极限
#include <cmath>					// 数据函数
#include <fstream>					// 文件输入输出
#include <cctype>					// 字符处理
#include <ctime>       				// 日期和时间函数
#include <cstdlib>					// 标准库
#include <cstdio>       			// 标准输入输出
#include <iomanip>					// 输入输出流格式设置	
#include <cstdarg> 					// 支持变长函数参数	
#include <cassert>					// 支持断言
#include <vector>                   // 动态数组
#include <list>                     // 双向链表
#include <deque>                    // 双端队列
#include <forward_list>
using namespace std;				// 标准库包含在命名空间std中P

const int climbSpeed = 10;
const int elevatorSpeed = 5;
const int elevatorCapacity = 25;
// 自定义类型
enum Status {SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW,RANGE_ERROR, DUPLICATE_ERROR,
	NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED};

#endif