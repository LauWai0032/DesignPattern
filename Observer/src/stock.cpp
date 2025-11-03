#include "./observer.hpp"
void Stock::notify() const
{
  for (auto it : Observers)
  {
    if (it->getTargetPrice() < _price)
    {
      it->receiveEvent();
    }
  }
}

void Stock::setStockPrice(const double &price)
{
  _price = price;
  notify();
}