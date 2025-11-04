// 包含观察者模式核心头文件，该头文件中声明了 Observer 类、Events 类及相关接口
#include "./observer.hpp"

/**
 * @brief 注册观察者到事件中心
 * @param ob 指向 Observer 类对象的指针，代表要注册的观察者实例
 * @details 将观察者对象添加到 Events 类的观察者列表（Observers）中，
 *          后续事件发生时，该观察者会收到通知
 */
void Events::obRegister(Observer *ob)
{
  // 使用 emplace_back 高效添加观察者指针到列表尾部（避免拷贝，直接构造）
  Observers.emplace_back(ob);
}

/**
 * @brief 从事件中心移除指定观察者
 * @param ob 指向要移除的 Observer 类对象的指针
 * @details 1. 在观察者列表中查找目标观察者指针
 *          2. 找到后从列表中删除该观察者
 *          3. 输出移除成功的日志信息（包含观察者名称）
 *          4. 若未找到目标观察者，则不执行任何操作
 */
void Events::obRemove(Observer *ob)
{
  // 调用 std::find 在观察者列表中查找目标观察者指针
  // Observers.begin()：列表起始迭代器，Observers.end()：列表结束迭代器
  auto it = std::find(Observers.begin(), Observers.end(), ob);

  // 检查是否找到目标观察者（it 不等于结束迭代器说明找到）
  if (it != Observers.end())
  {
    // 从列表中删除找到的观察者（erase 接收迭代器参数，删除该位置元素）
    Observers.erase(it);
    // 输出移除日志：通过观察者的 ob_getname() 方法获取名称，告知用户该观察者已被移除
    std::cout << ob->ob_getname() << " Remove!" << std::endl;
  }
}