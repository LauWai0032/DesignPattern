#pragma once        // 防止头文件被重复包含
#include <iostream> // 用于输入输出操作
#include <chrono>   // 用于时间相关操作（获取当前时间）
#include <string>   // 用于字符串处理
#include <ctime>    // 用于时间转换（将时间戳转为字符串）

// 支付方式基类（抽象类），定义支付方式的接口
class Paymethod
{
public:
  // 纯虚函数，定义支付方式的具体操作接口，子类需实现
  virtual void method() = 0;
  virtual ~Paymethod() = default;
};

// 支付宝支付类，继承自支付方式基类
class Alipay : public Paymethod
{
public:
  // 实现支付宝的具体支付操作
  void method() override;
};

// 微信支付类，继承自支付方式基类
class Wechatpay : public Paymethod
{
public:
  // 实现微信支付的具体支付操作
  void method() override;
};

// 支付流程基类，定义支付的整体流程框架
class Payment
{
public:
  // 构造函数，初始化支付金额
  Payment(double price) : _price(price) {}

  // 支付流程的主函数，final修饰表示子类不能重写此函数
  // 确保所有支付流程遵循统一的步骤
  virtual void paymentProcess(Paymethod *paymethod) const final;

  // 虚析构函数，确保子类对象销毁时能正确调用析构函数
  virtual ~Payment();

protected:
  // 创建订单的操作（支付流程步骤1）
  void createOrder() const;

  // 金额确认的纯虚函数（支付流程步骤2），子类需根据折扣规则实现
  virtual void amountConfirmation() const = 0;

  // 调用支付方式进行支付（支付流程步骤3）
  void paymentMethod(Paymethod *paymethod) const;

  // 记录支付日志（支付流程步骤4）
  void paymentLog() const;

  double _price; // 支付的原始金额（保护成员，子类可访问）
};

// 普通会员折扣类，继承自支付流程基类
class RegularMemberDiscount : public Payment
{
public:
  // 继承父类的构造函数，用于初始化支付金额
  using Payment::Payment;

  // 重写金额确认方法，实现普通会员的折扣规则
  void amountConfirmation() const override;

  // 析构函数
  ~RegularMemberDiscount();
};

// 银卡会员折扣类，继承自支付流程基类
class SilverMemberDiscount : public Payment
{
public:
  // 继承父类的构造函数，用于初始化支付金额
  using Payment::Payment;

  // 重写金额确认方法，实现银卡会员的折扣规则
  void amountConfirmation() const override;

  // 析构函数
  ~SilverMemberDiscount();
};

// 金卡会员折扣类，继承自支付流程基类
class GoldMemberDiscount : public Payment
{
public:
  // 继承父类的构造函数，用于初始化支付金额
  using Payment::Payment;

  // 重写金额确认方法，实现金卡会员的折扣规则
  void amountConfirmation() const override;

  // 析构函数
  ~GoldMemberDiscount();
};