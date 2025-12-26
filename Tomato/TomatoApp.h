#ifndef TOMATOAPP_H
#define TOMATOAPP_H

#include <vector>
#include <string>
#include "modal/User.h"
#include "modal/Resteraunt.h"
#include "modal/Cart.h"
#include "manager/ResterauntManager.h"
#include "manager/OrderManager.h"
#include "strategies/PaymentStrategy.h"
#include "Factory/NowOrderFactory.h"
#include "Factory/ScheduleOrderFactory.h"
#include "services/NotificationService.h"

using namespace std;

class Tomato{
    Tomato(){
        initializeRestaraunt();
    }

    void initializeRestaraunt(){
        Restaurant* restaurant1 = new Restaurant("Bikaner","Delhi");
        restaurant1->addMenuItem(MenuItem("P1", "Chole Bhature", 120));
        restaurant1->addMenuItem(MenuItem("P1", "Dhokla", 50));

        Restaurant* restaurant2 = new Restaurant("Haldiram", "Kolkata");
        restaurant2->addMenuItem(MenuItem("P1", "Raj Kachori", 80));
        restaurant2->addMenuItem(MenuItem("P2", "Pav Bhaji", 100));
        restaurant2->addMenuItem(MenuItem("P3", "Dhokla", 50));

        Restaurant* restaurant3 = new Restaurant("Saravana Bhavan", "Chennai");
        restaurant3->addMenuItem(MenuItem("P1", "Masala Dosa", 90));
        restaurant3->addMenuItem(MenuItem("P2", "Idli Vada", 60));
        restaurant3->addMenuItem(MenuItem("P3", "Filter Coffee", 30));

        RestaurantManager* res_manager =  RestaurantManager::getInstance();
        res_manager->addResteraunt(restaurant1);
        res_manager->addResteraunt(restaurant2);
        res_manager->addResteraunt(restaurant3);

    }

    vector<Restaurant*> searchByLocation(string loc){
        return RestaurantManager::getInstance()->getResteraunt(loc);
    }
    void selectRestaurant(User* user, Restaurant* restaurant) {
        Cart* cart = user->getCart();
        cart->setRestaurant(restaurant);
    }
    void addItemsinCart(User* user, const string& item_code){
        Restaurant* res = user->getCart()->getRestaurant();
        if(res == nullptr) cerr<<"Please select restaraunt\n";
        else{
            for(auto& item:res->getMenu()){
                if(item->getCode() == item_code){
                    user->getCart()->addMenuItem(item);
                    break;
                }
            }
        }
    }

    Order* checkoutNow(User* u, string& orderType, PaymentStrategy* payment){
        return checkout(u, orderType, payment,new NowOrderFactor());
    }

    Order* checkout(User* u, string& orderType, PaymentStrategy* payment, OrderFactory* orderfactory)
    {
        if(u->getCart()->isEmpty()) return nullptr;
        
        Cart* user_cart = u->getCart();
        Restaurant* res = user_cart->getRestaurant();
        vector<MenuItem> items = user_cart->getMenuItem();
        double total = user_cart->getTotal();

        Order* order = orderfactory->CreateOrder(u,user_cart,res,items,payment,total,orderType);
    }

    void payForOrder(User* user, Order* order) {
        bool isPaymentSuccess = order->processPayment();

        // clear user cart if payment is successful.
        if(isPaymentSuccess) {
            NotificationService* notification = new NotificationService();
            notification->notify(order);
            user->getCart()->isClear();
        }  
    }

    void printUserCart(User* user) {
        cout << "Items in cart:" << endl;
        cout << "------------------------------------" << endl;
        for (const auto& item : user->getCart()->getMenuItem()) {
            cout << item.getCode() << " : " << item.getName() << " : ₹" << item.getPrice() << endl;
        }
        cout << "------------------------------------" << endl;
        cout << "Grand total : ₹" << user->getCart()->getTotal() << endl;
    }

};

#endif