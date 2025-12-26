#ifndef ORDERFACTORY_H
#define ORDERFACTORY_H

#include<iostream>
#include "../modal/Order.h"
#include "../modal/Cart.h"
#include "../modal/Resteraunt.h"
#include "../strategies/PaymentStrategy.h"


class OrderFactory{
  public:
  virtual Order* CreateOrder(User* u, Cart* cart, Restaurant* rest, const vector<MenuItem> menu, PaymentStrategy* payment_strategy, double total, const string&orderType) =0;

 virtual ~OrderFactory(){}
};
#endif

