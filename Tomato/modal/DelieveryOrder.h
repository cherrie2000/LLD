#ifndef DELIEVERYORDER_H
#define DELIEVERYORDER_H

#include "Order.h"
#include <string>
using namespace std;
class Delievery_Order: public Order {
    private:
    string user_address;
    public:
    Delievery_Order(){
        user_address="";
    }
    string getType() const override{
        return "Delievery";
    }
    void setAddress(const string&s){
        user_address =s;
    }
     string getAddress() const{
        return user_address;
     }
};
#endif