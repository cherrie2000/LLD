#ifndef CART_H
#define CART_H

#include<iostream>
#include<vector>
#include<string>
#include "Resteraunt.h"
#include "MenuItem.h"
#include <iterator>

class Cart{
  private:
  Restaurant* res;
  vector<MenuItem*> items;
  public:
  Cart(){
    res = nullptr;
  }
  void addMenuItem(const MenuItem* menu){
    if(res==nullptr){
        cerr<<"Please select a restaurant\n";
        return;
    }
    items.push_back(menu);

  }
  const vector<MenuItem*>& getMenuItem() const{

    return items;
  }

  const double getTotal() const{
    double sum = 0.0;
    for(auto it: items){
        sum+=it->getPrice();
    }
    return sum;
  }
  void setRestaurant(Restaurant* r){
    res = r;
  }
  const Restaurant* getRestaurant() const{
    return res;
  }
  void isClear() {
        items.clear();
        res = nullptr;
  }
  bool isEmpty() const{
    return (!res || items.empty());
  }
  
};
#endif
