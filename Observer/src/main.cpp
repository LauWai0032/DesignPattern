// 包含观察者模式核心头文件（声明 Observer、Trader、Stock、Events 等类及接口）
#include "./observer.hpp"

// 程序主函数，演示观察者模式的核心流程：注册观察者、触发事件、通知观察者
int main()
{
  // 1. 创建观察者实例：Trader（交易者）是 Observer 的子类，代表关注股票的观察者
  // 构造参数：交易者名称 "TrA"，初始资金 200.0
  Observer *traderA = new Trader("TrA", 200.0);

  // 2. 创建被观察者（主题）实例：Stock（股票）是 Events 的子类，代表被观察的目标对象
  // 构造参数：股票代码 "000201"，初始价格 100（单位根据业务场景定义，如元）
  Events *stockA = new Stock("000201", 100);

  // 3. 注册观察者：将交易者 traderA 注册到股票 stockA 的观察者列表中
  // 后续 stockA 的价格发生变化时，会自动通知所有已注册的观察者
  stockA->obRegister(traderA);

  // 4. 触发事件：修改股票价格（触发被观察者状态变更）
  // 调用 setStockPrice 会更新股票价格，并自动通知所有注册的观察者（如 traderA）
  stockA->setStockPrice(300.0); // 股票价格从 100 涨到 300，通知 traderA
  stockA->setStockPrice(150.0); // 股票价格从 300 跌到 150，通知 traderA

  // 5. 手动释放动态分配的内存（避免内存泄漏）
  // 注意释放顺序：先释放观察者，再释放被观察者（确保被观察者引用观察者时对象仍有效）
  delete traderA;
  delete stockA;

  // 程序正常退出
  return 0;
}