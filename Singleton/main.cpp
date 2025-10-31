#include "singleton.hpp"
class test : public Singleton<test>
{
};
int main()
{
  Singleton<test> *singleton = Singleton<test>::getInstance();
  return 0;
}