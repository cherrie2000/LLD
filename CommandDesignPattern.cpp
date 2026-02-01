#include<bits/stdc++.h>
using namespace std; 

class ICommand{
    public:
    virtual void execute()=0;
    virtual void undo()=0;
    virtual ~ICommand(){};
};
class Light{
    public:
    void on(){
        cout<<"Light is on\n";
    }
    void off(){
        cout<<"Light is off\n";
    }
};

class Fan{
    public:
    void on(){
        cout<<"Fan is on\n";
    }
    void off(){
        cout<<"Fan is off\n";
    }
};
class LightCommand: public ICommand{
    private:
    Light* l;
    public:
    LightCommand(Light* lt){
        l = lt;
    }
    void execute() override{
        l->on();
    }
    void undo() override{
        l->off();
    }
};
class FanCommand: public ICommand{
    private:
    Fan* f;
    public:
    FanCommand(Fan* fan){
        f = fan;
    }
    void execute() override{
        f->on();
    }
    void undo() override{
        f->off();
    }
};

class RemoteController{
    private:
    static const int count = 2;
    ICommand* press[count];
    bool pressed[count];
    public:
    RemoteController(){
        for(int i=0;i<count;i++){
            press[i] = nullptr;
            pressed[i] = false;
        }
    }

    void setCommand(int i, ICommand* cmd){
        if(i>=0 && i<count){
            if(press[i]!=nullptr){
                delete press[i];
            }
            press[i] = cmd;
            pressed[i] = false;
        }
    }
    void PressButton(int i){
        if(i<0 || i>=count) cout<<"Invalid Button Pressed\n";
        if(pressed[i]){
            press[i]->undo();
        }
        else{
            press[i]->execute();
        }
        pressed[i] = !pressed[i];
    }
};
int main(){
    Light* ceilingLight = new Light();
    Fan* fan = new Fan();

    RemoteController* remote =  new RemoteController();
    remote->setCommand(0,new LightCommand(ceilingLight));
    remote->setCommand(1, new FanCommand(fan));

    remote->PressButton(0);
    remote->PressButton(0);

    remote->PressButton(1);
    remote->PressButton(1);

}
