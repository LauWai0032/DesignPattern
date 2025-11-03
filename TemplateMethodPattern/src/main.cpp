#include "./templatemethodpattern.hpp" // 包含模板方法模式相关的类声明

int main()
{
  // 创建普通会员支付对象，原始金额100.0
  // 父类指针指向子类对象，体现多态特性
  Payment *regularmember = new RegularMemberDiscount(100.0);

  // 创建银卡会员支付对象，原始金额50.0
  Payment *silverMember = new SilverMemberDiscount(50.0);

  // 创建支付宝支付方式对象
  Paymethod *alipaymethod = new Alipay();

  // 创建微信支付方式对象
  Paymethod *wechatpaymethod = new Wechatpay();

  // 普通会员使用支付宝进行支付
  // 调用模板方法paymentProcess，固定流程为：创建订单->确认金额(无折扣)->支付宝支付->记录日志
  regularmember->paymentProcess(alipaymethod);

  // 银卡会员使用微信支付进行支付
  // 调用模板方法paymentProcess，固定流程为：创建订单->确认金额(9折)->微信支付->记录日志
  silverMember->paymentProcess(wechatpaymethod);

  // 释放动态分配的对象，避免内存泄漏
  delete regularmember;   // 释放普通会员支付对象（会先调用子类析构，再调用父类析构）
  delete silverMember;    // 释放银卡会员支付对象
  delete alipaymethod;    // 释放支付宝支付方式对象
  delete wechatpaymethod; // 释放微信支付方式对象

  return 0;
}