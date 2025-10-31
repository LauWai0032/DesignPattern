#pragma once
#include <memory>
#include <mutex>
template <typename T>
class Singleton
{
protected:
  Singleton() = default;
  ~Singleton() = default;

public:
  Singleton(const Singleton &) = delete;
  Singleton &operator=(const Singleton &) = delete;
  Singleton(Singleton &&) = delete;
  Singleton &operator=(Singleton &&) = delete;
  static T &getInstance()
  {
    if (!_instance)
    {
      std::lock_guard<std::mutex> lock(_mutex);
      if (!_instance)
      {
        _instance.reset(new (T));
      }
    }
  }

private:
  static std::unique_ptr<T> _instance;
  static std::mutex _mutex;
};
template <typename T>
std::unique_ptr<T> Singleton<T>::_instance = nullptr;

template <typename T>
std::mutex Singleton<T>::_mutex;
