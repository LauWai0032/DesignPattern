#include <mutex>
#include <iostream>
#include <memory>
int main()
{
  std::mutex _mutex;
  std::lock_guard<std::mutex> lock(_mutex);
  return 0;
}