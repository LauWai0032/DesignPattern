#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
class Observer
{
public:
  virtual ~Observer() = default;
  std::string ob_getname() const;
  Observer(const std::string &obname) : _ob_name(obname) {}
  virtual double getTargetPrice() const = 0;
  virtual void receiveEvent() const = 0;

protected:
  std::string _ob_name;
};
class Events
{
public:
  virtual ~Events() = default;
  virtual void notify() const = 0;
  virtual void obRegister(Observer *ob);
  virtual void obRemove(Observer *ob);
  virtual void setStockPrice(const double &price) = 0;

protected:
  std::vector<Observer *> Observers;
};

class Stock : public Events
{
public:
  ~Stock() = default;
  Stock(const std::string &stock_id, const double &price) : _stock_id(stock_id), _price(price) {}
  void setStockPrice(const double &price) override;
  void notify() const override;

private:
  std::string _stock_id;
  double _price;
};

class Trader : public Observer
{
private:
  double _targetPrice;

public:
  Trader(const std::string &traderName, const double &targetPrice) : Observer(traderName), _targetPrice(targetPrice) {}
  void setTargetPrice(const double &targetPrice);
  double getTargetPrice() const override;
  void receiveEvent() const override;
};