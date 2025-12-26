#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H
#include "../modal/Order.h"
class OrderManager{
  private:
  vector<Order*> orders;
  static OrderManager* instance;
  OrderManager(){}  
  public:
   static OrderManager* getInstance(){
     if(instance){
        instance =  new OrderManager;
     }
     return instance;
   }
   void addOrder(Order* order) const{
    orders.push_back(order);
   }
       void listOrders() {
        cout << "\n--- All Orders ---" << endl;
        for (auto order : orders) {
            cout << order->getType() << " order for " << order->getUser()->getName()
                    << " | Total: ₹" << order->getTotal()
                    << " | At: " << order->getScheduled() << endl;
        }
    }
};
#endif