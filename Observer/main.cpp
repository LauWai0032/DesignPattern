#include "./observer.hpp"
#include <memory>
int main()
{
  // std::unique_ptr<Observer> traderA = std::make_unique<Trader>("TrA", 200.0);
  // std::unique_ptr<Events> stockA = std::make_unique<Stock>("000201", 100);
  Observer *traderA = new Trader("TrA", 200.0);
  Events *stockA = new Stock("000201", 100);
  stockA->obRegister(traderA);
  stockA->setStockPrice(300.0);
  stockA->setStockPrice(150.0);
  delete traderA;
  delete stockA;
  return 0;
}