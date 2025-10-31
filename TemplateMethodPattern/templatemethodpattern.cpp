#include "./templatemethodpattern.hpp" // 包含对应的头文件，声明了各类和方法

// 支付流程主函数的实现
// 模板方法模式的核心：定义固定的支付流程步骤，子类无法修改此流程
void Payment::paymentProcess(Paymethod *paymethod) const
{
  createOrder();            // 步骤1：创建订单
  amountConfirmation();     // 步骤2：确认金额（子类实现具体折扣逻辑）
  paymentMethod(paymethod); // 步骤3：执行支付（调用具体支付方式）
  paymentLog();             // 步骤4：记录支付日志
}

// 创建订单的具体实现
void Payment::createOrder() const
{
  std::cout << "Create Order" << std::endl; // 输出"创建订单"提示
}

// 调用支付方式进行支付的实现
void Payment::paymentMethod(Paymethod *paymethod) const
{
  paymethod->method(); // 多态调用：根据传入的支付方式对象，执行对应支付操作
}

// 记录支付日志的实现（包含时间戳）
void Payment::paymentLog() const
{
  char buffer[128];                                // 用于存储格式化后的时间字符串
  const std::string &format = "%Y-%m-%d %H:%M:%S"; // 时间格式：年-月-日 时:分:秒

  // 获取当前系统时间并转换为时间戳
  std::time_t time_tp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

  // 将时间戳格式化为指定字符串
  std::strftime(buffer, sizeof(buffer), format.c_str(), std::localtime(&time_tp));

  // 输出订单完成时间
  std::cout << "Order Completion Time:" << std::string(buffer) << std::endl;
}

// 普通会员的金额确认实现（无折扣）
void RegularMemberDiscount::amountConfirmation() const
{
  std::cout << "Price:" << _price << std::endl; // 直接输出原始价格
}

// 银卡会员的金额确认实现（9折优惠）
void SilverMemberDiscount::amountConfirmation() const
{
  std::cout << "Price:" << 0.9 * _price << std::endl; // 输出9折后的价格
}

// 金卡会员的金额确认实现（8折优惠）
void GoldMemberDiscount::amountConfirmation() const
{
  std::cout << "Price:" << 0.8 * _price << std::endl; // 输出8折后的价格
}

// 支付宝支付的具体实现
void Alipay::method()
{
  std::cout << "Using Alipay!" << std::endl; // 输出"使用支付宝支付"提示
}

// 微信支付的具体实现
void Wechatpay::method()
{
  std::cout << "Using Wechatpay!" << std::endl; // 输出"使用微信支付"提示
}

// Payment基类析构函数的实现
Payment::~Payment()
{
  std::cout << "Payment Release!" << std::endl; // 输出"Payment类资源释放"提示
}

// 普通会员折扣类析构函数的实现
RegularMemberDiscount::~RegularMemberDiscount()
{
  std::cout << "RegularMemberDiscount Release!" << std::endl; // 输出"普通会员折扣类资源释放"提示
}

// 银卡会员折扣类析构函数的实现
SilverMemberDiscount::~SilverMemberDiscount()
{
  std::cout << "SilverMemberDiscount Release!" << std::endl; // 输出"银卡会员折扣类资源释放"提示
}

// 金卡会员折扣类析构函数的实现
GoldMemberDiscount::~GoldMemberDiscount()
{
  std::cout << "GoldMemberDiscount Release!" << std::endl; // 输出"金卡会员折扣类资源释放"提示
}