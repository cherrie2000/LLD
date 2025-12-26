#ifndef ORDER_H
#define ORDER_H
#include<iostream>
#include<string>
#include "Resteraunt.h"
#include "MenuItem.h"
#include "User.h"
#include "../strategies/PaymentStrategy.h"
using namespace std;

class Order{
private:
   static int next_order_id;
   int order_id; 
   User* user;
   Restaurant* restaraunt;
   vector<MenuItem> items;
   PaymentStrategy* payment_method;
   double amt;
   string schedule;

public:
   Order(){
     user = nullptr, restaraunt = nullptr, payment_method =nullptr;
     schedule=""; amt = 0.0;
     order_id = ++next_order_id;
   } 
   virtual ~Order(){
    delete payment_method;
   }

       bool processPayment() {
        if (payment_method) {
            payment_method->pay(amt);
            return true;
        } else {
            cout << "Please choose a payment mode first" << endl;
            return false;
        }
    }

    virtual string getType() const = 0;

      void setUser(User* u) {
        user = u;
    }

    User* getUser() const {
        return user;
    }

    void setRestaurant(Restaurant* r) {
        restaraunt = r;
    }

    Restaurant* getRestaurant() const {
        return restaraunt;
    }

    void setItems(const vector<MenuItem>& its) {
        items = its;
        amt = 0;
        for (auto &i : items) {
            amt += i.getPrice();
        }
    }

    const vector<MenuItem>& getItems() const {
        return items;
    }

    void setPaymentStrategy(PaymentStrategy* p) {
        payment_method = p;
    }

    void setScheduled(const string& s) {
        schedule = s;
    }

    string getScheduled() const {
        return schedule;
    }

    double getTotal() const {
        return amt;
    }

    void setTotal(int total) {
        this->amt = amt;
    }
};
int  Order::next_order_id=0;
#endif