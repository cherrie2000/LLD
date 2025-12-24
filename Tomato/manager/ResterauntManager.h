#ifndef RESTAURANT_MANAGER_H
#define RESTAURANT_MANAGER_H

#include<iostream>
#include<vector>
#include<string>
#include <algorithm>
#include "../modal/Resteraunt.h"
using namespace std;
class RestaurantManager{
    private:
  vector<Restaurant*> RestaurantList;
  static RestaurantManager* instance;

  RestaurantManager(){}

  public:
  static RestaurantManager* getInstance(){
    if(!instance) instance= new RestaurantManager();
    return instance;
  }

  void addResteraunt(Restaurant* restaurant){
    RestaurantList.push_back(restaurant);
  }

  vector<Restaurant*> getResteraunt(string loc){
    vector<Restaurant*> result;
    transform(loc.begin(), loc.end(), loc.begin(), ::tolower);
    for(auto res:ResterauntList){
        string res_loc = res->getLocation();
        transform(res_loc.begin(), res_loc.end(), res_loc.begin(), ::tolower);
        if(res_loc==loc){
            result.push_back(res);
        }
    }
    return result;
  }

};
RestaurantManager* RestaurantManager::instance = nullptr;
#endif