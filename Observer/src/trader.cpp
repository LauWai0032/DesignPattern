#include "./observer.hpp"
void Trader::setTargetPrice(const double &targetPrice)
{
  _targetPrice = targetPrice;
}

double Trader::getTargetPrice() const
{
  return _targetPrice;
}

void Trader::receiveEvent() const
{
  std::cout << _ob_name << " Receive!" << std::endl;
}