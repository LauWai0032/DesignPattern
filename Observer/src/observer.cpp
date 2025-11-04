// 包含观察者基类 Observer 的声明头文件，确保类成员和接口可被正确识别
#include "./observer.hpp"

/**
 * @brief 观察者基类的名称获取接口（常量成员函数）
 * @return std::string 观察者的名称（返回 _ob_name 成员变量的值）
 * @details 1. 该函数是 Observer 类的公共成员函数，供外部（如被观察者 Events 类）获取观察者名称
 *          2. 末尾 const 修饰：表明该函数不会修改类的任何成员变量（只读操作），确保函数调用安全性
 *          3. 核心作用：在观察者被移除、日志输出等场景中，提供可识别的观察者标识
 *          4. _ob_name 是 Observer 类的成员变量（存储观察者名称），通过构造函数初始化
 */
std::string Observer::ob_getname() const
{
  // 直接返回观察者的名称成员变量，实现简单的 getter 功能
  return _ob_name;
}