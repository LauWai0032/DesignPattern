// 包含观察者模式核心头文件，声明了 Stock 类、Observer 类等相关接口和成员
#include "./observer.hpp"

/**
 * @brief Stock 类（具体被观察者）的通知实现函数（重写自 Events 基类的纯虚函数）
 * @details 1. 遍历所有已注册的观察者，筛选出满足条件的观察者并发送通知
 *          2. 通知条件：观察者的目标价格 < 股票当前价格（即股票价格高于观察者预期时触发通知）
 *          3. 核心逻辑：仅向符合条件的观察者调用 receiveEvent() 接口，实现"条件触发通知"
 */
void Stock::notify() const
{
  // 范围 for 循环遍历观察者列表（Observers 是父类 Events 的受保护成员，存储所有注册的 Observer 指针）
  for (auto it : Observers)
  {
    // 筛选条件：判断观察者的目标价格（getTargetPrice()）是否小于股票当前价格（_price）
    // getTargetPrice() 是 Observer 基类的纯虚函数，由具体观察者（如 Trader）实现
    if (it->getTargetPrice() < _price)
    {
      // 向符合条件的观察者发送通知：调用观察者的接收事件接口
      // receiveEvent() 是 Observer 基类的纯虚函数，子类需实现具体响应逻辑（如输出交易提示）
      it->receiveEvent();
    }
  }
}

/**
 * @brief Stock 类的股票价格设置函数（重写自 Events 基类的纯虚函数）
 * @param price 新的股票价格（const 引用传递，避免拷贝，同时防止修改实参）
 * @details 1. 核心功能：更新股票当前价格，并自动触发通知机制
 *          2. 流程：先更新价格成员 _price，再调用 notify() 通知所有符合条件的观察者
 *          3. 设计意义：将"状态更新"与"通知触发"绑定，确保价格变化后观察者能及时收到消息
 */
void Stock::setStockPrice(const double &price)
{
  // 更新股票当前价格（_price 是 Stock 类的私有成员，存储最新股票价格）
  _price = price;

  // 价格更新后，调用 notify() 函数触发通知，通知所有符合条件的观察者
  notify();
}