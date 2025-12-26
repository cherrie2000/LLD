#ifndef PAYMENTSTRATEGY_H
#define PAYMENTSTRATEGY_H

class PaymentStrategy{
public:
  virtual void pay(double amt =0) = 0;
  virtual ~PaymentStrategy(){}
};
#endif