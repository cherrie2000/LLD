#ifndef NOWORDERFACTORY_H
#define NOWORDERFACTORY_H

#include<iostream>
#include "OrderFactory.h"
#include "../modal/DelieveryOrder.h"
#include "../modal/PickupOrder.h"
using namespace std;
class NowOrderFactor: public OrderFactory{
    


    public:
    NowOrderFactor(){
         
    }

    Order* CreateOrder(User* u, Cart* cart, Restaurant* rest, const vector<MenuItem>&menu, PaymentStrategy* payment_strategy, double total, const string&orderType) override{
        Order* order = nullptr;
        if(orderType == "Delievery"){
            auto delievery = new Delievery_Order();
            delievery->setAddress( u->getAddress());
            order = delievery;
        }
        else{
            auto pickup = new Pickup_Order();
            pickup->setAddress( u->getAddress());
            order = pickup;            
        }
        order->setUser(u);
        order->setRestaurant(rest);
        order->setItems(menu);
        order->setScheduled(orderType);
        order->setPaymentStrategy(payment_strategy);
        order->setTotal(total);
        return order;
    }

};
#endif