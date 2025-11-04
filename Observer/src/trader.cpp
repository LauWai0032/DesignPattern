// 包含观察者模式核心头文件，声明了 Trader 类、Observer 基类等相关接口和成员
#include "./observer.hpp"

/**
 * @brief 交易者（具体观察者）的目标价格设置函数
 * @param targetPrice 新的目标价格（const 引用传递，避免拷贝，同时防止修改实参）
 * @details 1. 普通成员函数，用于动态调整交易者的目标价格（如修改买入/卖出阈值）
 *          2. 直接赋值给私有成员变量 _targetPrice，实现简单的 setter 功能
 *          3. 无返回值，仅负责更新状态，后续可根据需求扩展参数校验（如价格非负）
 */
void Trader::setTargetPrice(const double &targetPrice)
{
  // 更新交易者的目标价格（_targetPrice 是 Trader 类的私有成员，存储目标交易价格）
  _targetPrice = targetPrice;
}

/**
 * @brief 交易者（具体观察者）的目标价格获取函数（重写自 Observer 基类的纯虚函数）
 * @return double 交易者当前的目标价格（返回私有成员 _targetPrice 的值）
 * @details 1. const 修饰：表明该函数不修改类成员变量，仅提供只读访问
 *          2. 核心作用：被被观察者（如 Stock 类）调用，用于判断是否满足通知条件
 *          3. 实现观察者与被观察者的解耦：被观察者无需知道交易者内部逻辑，仅通过接口获取所需数据
 */
double Trader::getTargetPrice() const
{
  // 直接返回私有成员 _targetPrice 的值，实现纯虚函数要求的 getter 功能
  return _targetPrice;
}

/**
 * @brief 交易者（具体观察者）的事件接收响应函数（重写自 Observer 基类的纯虚函数）
 * @details 1. 当被观察者（如 Stock 类）触发通知且满足条件时，会调用此函数
 *          2. 目前实现为输出日志：告知用户该交易者已收到事件通知
 *          3. 可根据业务需求扩展：如添加交易决策逻辑（买入/卖出）、记录日志、发送提醒等
 *          4. const 修饰：确保响应事件时不修改交易者自身状态（若需修改可移除 const）
 */
void Trader::receiveEvent() const
{
  // 输出通知日志：通过父类保护成员 _ob_name 获取交易者名称，明确标识接收通知的对象
  std::cout << _ob_name << " Receive!" << std::endl;
}