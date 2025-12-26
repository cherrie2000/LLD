#ifndef USER_H
#define USER_H

#include "cart.h"
#include<string>
using namespace std;
class User{
    private:
    int userId;
    string name;
    string address;
    Cart* cart;

    public:
    User(int&id, string&name, string&address){
        userId = id;
        this->name = name;
        this->address = address;
        cart = new Cart();
    }

    ~User(){
        delete cart;
    }

    string getName() const{
        return name;
    }
    void setName(const string&n){
        name = n;
        return;
    }
    string getAddress() const{
        return address;
    }
    void setAddress(const string&add){
        address = add;
        return;
    }
    Cart* getCart() const{
        return cart;
    }

};
#endif