#include<iostream>
#include <string>
using namespace std;

class Character{
    public:
   virtual string getAbilities() =0;
   virtual ~Character(){};
};

class Mario: public Character{
  string getAbilities() override{
    return "Mario ";
  }  
};

class ClassDecoractor:public Character{
  protected:
  Character* c;
  public:
  ClassDecoractor(Character* ch){
    c = ch;
  }
};

class HeightUp:public ClassDecoractor{
  public:
  HeightUp(Character*c):ClassDecoractor(c){};
    string getAbilities() override{
    return c->getAbilities()+" HeightUp";
  }  
};
class GunUp:public ClassDecoractor{
  public:
  GunUp(Character*c):ClassDecoractor(c){};
    string getAbilities() override{
    return c->getAbilities()+" GunUp";
  }  
};

int main(){
    Character* mario = new Mario();
    cout<<mario->getAbilities()<<"\n";

    mario = new HeightUp(mario);
    cout<<mario->getAbilities()<<"\n";

    mario = new GunUp(mario);
    cout<<mario->getAbilities()<<"\n";
}