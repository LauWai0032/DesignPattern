#include "./observer.hpp"
void Events::obRegister(Observer *ob)
{
  Observers.emplace_back(ob);
}

void Events::obRemove(Observer *ob)
{
  auto it = std::find(Observers.begin(), Observers.end(), ob);
  if (it != Observers.end())
  {
    Observers.erase(it);
    std::cout << ob->ob_getname() << "Remove!" << std::endl;
  }
}
