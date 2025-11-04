// 防止头文件重复包含（替代传统的 #ifndef-#define-#endif 结构，编译器兼容性需注意）
#pragma once

// 包含标准库头文件：提供输入输出、容器、字符串处理等基础功能
#include <iostream>  // 用于 std::cout 等日志输出
#include <vector>    // 用于 std::vector，存储观察者列表
#include <string>    // 用于 std::string，处理名称、ID 等字符串
#include <algorithm> // 用于 std::find，在观察者列表中查找目标对象

/**
 * @brief 观察者基类（Observer）
 * @details 定义所有观察者的统一接口，被观察者（Events）通过该接口通知观察者
 *          所有具体观察者（如 Trader）需继承此类并实现纯虚函数
 */
class Observer
{
public:
  // 虚析构函数：确保子类对象销毁时能正确调用子类析构函数，避免内存泄漏
  virtual ~Observer() = default;

  // 获取观察者名称的成员函数（const 修饰，不修改成员变量）
  std::string ob_getname() const;

  // 构造函数：初始化观察者名称
  // 参数 obname：观察者的唯一标识名称（如交易者名称 "TrA"）
  Observer(const std::string &obname) : _ob_name(obname) {}

  // 纯虚函数：获取观察者的目标价格（如交易者的目标交易价格）
  // 子类需根据自身逻辑实现，返回具体的目标价格
  virtual double getTargetPrice() const = 0;

  // 纯虚函数：接收事件通知的接口
  // 被观察者状态变化时，会调用此函数通知观察者，子类需实现具体响应逻辑
  virtual void receiveEvent() const = 0;

protected:
  // 观察者名称：受保护成员，子类可访问，外部需通过 ob_getname() 获取
  std::string _ob_name;
};

/**
 * @brief 被观察者基类（Events）
 * @details 定义被观察者的统一接口，管理观察者列表（注册、移除）并提供通知能力
 *          所有具体被观察者（如 Stock）需继承此类并实现纯虚函数
 */
class Events
{
public:
  // 虚析构函数：确保子类对象销毁时能正确调用子类析构函数
  virtual ~Events() = default;

  // 纯虚函数：通知所有已注册的观察者
  // 被观察者状态变化时调用，子类需实现遍历观察者列表并触发通知的逻辑
  virtual void notify() const = 0;

  // 虚函数：注册观察者（将观察者添加到列表）
  // 参数 ob：指向 Observer 实例的指针，代表要注册的观察者
  virtual void obRegister(Observer *ob);

  // 虚函数：移除观察者（将观察者从列表中删除）
  // 参数 ob：指向 Observer 实例的指针，代表要移除的观察者
  virtual void obRemove(Observer *ob);

  // 纯虚函数：设置被观察者关联的股票价格（针对股票场景的专用接口）
  // 参数 price：新的股票价格，子类需实现价格更新及触发通知的逻辑
  virtual void setStockPrice(const double &price) = 0;

protected:
  // 观察者列表：存储所有已注册的 Observer 指针，受保护成员，子类可访问
  std::vector<Observer *> Observers;
};

/**
 * @brief 具体被观察者：股票（Stock）
 * @details 继承自 Events 类，实现股票相关的被观察者逻辑，管理股票ID和价格，
 *          价格变化时通知所有注册的观察者（如 Trader）
 */
class Stock : public Events
{
public:
  // 析构函数：默认实现（无额外动态内存需要释放）
  ~Stock() = default;

  // 构造函数：初始化股票ID和初始价格
  // 参数 stock_id：股票的唯一标识（如 "000201"）
  // 参数 price：股票的初始价格
  Stock(const std::string &stock_id, const double &price) : _stock_id(stock_id), _price(price) {}

  // 重写父类函数：设置股票价格
  // 功能：更新股票价格，并调用 notify() 通知所有观察者价格变化
  void setStockPrice(const double &price) override;

  // 重写父类函数：通知所有注册的观察者
  // 功能：遍历观察者列表，调用每个观察者的 receiveEvent() 函数传递通知
  void notify() const override;

private:
  // 股票ID：私有成员，唯一标识一支股票，仅本类可访问
  std::string _stock_id;
  // 股票当前价格：私有成员，存储股票的最新价格，仅本类可访问
  double _price;
};

/**
 * @brief 具体观察者：交易者（Trader）
 * @details 继承自 Observer 类，实现交易者相关的观察者逻辑，
 *          持有目标交易价格，接收股票价格变化通知并响应
 */
class Trader : public Observer
{
private:
  // 交易者的目标价格：私有成员，如交易者设定的"低于此价格买入"或"高于此价格卖出"的阈值
  double _targetPrice;

public:
  // 构造函数：初始化交易者名称和目标价格
  // 参数 traderName：交易者名称（传递给父类 Observer 的构造函数）
  // 参数 targetPrice：交易者的初始目标价格
  Trader(const std::string &traderName, const double &targetPrice) : Observer(traderName), _targetPrice(targetPrice) {}

  // 普通成员函数：修改交易者的目标价格
  // 参数 targetPrice：新的目标价格，用于动态调整交易策略
  void setTargetPrice(const double &targetPrice);

  // 重写父类纯虚函数：获取交易者的当前目标价格
  double getTargetPrice() const override;

  // 重写父类纯虚函数：接收股票价格变化通知
  // 功能：根据股票最新价格和自身目标价格，执行具体响应逻辑（如输出交易提示）
  void receiveEvent() const override;
};