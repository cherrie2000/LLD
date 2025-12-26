#ifndef CREDITCARDPAYMENT_H
#define CREDITCARDPAYMENT_H

#include<iostream>
#include<string>
#include "PaymentStrategy.h"
using namespace std;

class CreditCardPayment: public PaymentStrategy{
    private:
     string cardNumber;
     public:
     CreditCardPayment(const string& num){
        cardNumber = num;
     }
     void pay(double amt) override{
        cout << "Paid ₹" << amt << " using Credit Card (" << cardNumber << ")" << endl;
     }
};
#endif