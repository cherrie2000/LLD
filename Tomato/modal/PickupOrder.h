#ifndef PICKUPORDER_H
#define PICKUPORDER_H

#include "Order.h"
#include <string>
class Pickup_Order: public Order {
    private:
    string rest_address;
    public:
    Pickup_Order(){
        rest_address="";
    }
    string getType() const override{
        return "Pickup";
    }
    void setAddress(const string&s){
        rest_address =s;
    }
     string getAddress() const{
        return rest_address;
     }
};
#endif