#include<iostream>
#include<vector>
#include<string>
#include <algorithm>
using namespace std;

class ISubscriber{
public:
virtual void Update() =0;
virtual ~ISubscriber(){}

};

class IChannel{
    public:
    virtual void Subscribed(ISubscriber*)=0;
    virtual void Unsubscribed(ISubscriber*)=0;
    virtual void notify()=0;
    virtual ~IChannel(){}
};

class Channel:public IChannel{
    private:
    string channel;
    vector<ISubscriber*> subscriberList;
    string latestVideo;
    public:
    Channel(string name){
        channel = name;
    }
    void Subscribed(ISubscriber* sub) override{
        if(find(subscriberList.begin(),subscriberList.end(),sub)==subscriberList.end())
        subscriberList.push_back(sub);
        return;
    }
    void Unsubscribed(ISubscriber* sub) override{
        auto it = find(subscriberList.begin(),subscriberList.end(),sub);
        subscriberList.erase(it);
        return;
    }
    void notify() override{
        for(auto it:subscriberList){
            it->Update();
        }
    }
    void UploadNewVideo(const string&name){
        latestVideo = name;
         cout << "\n[" << channel << " uploaded \"" << name << "\"]\n";
        notify();
    }
    string getLatestVideoDetail() const{
        return "\nCheckout our new Video : " + latestVideo + "\n";
    }

};
class Subscriber:public ISubscriber{
   private:
   string name;
   Channel* channel;
   public:
   Subscriber(string name , Channel* channel){
    this->name = name;
    this->channel = channel;
   }

   void Update() override{
     cout << "Hey " << name << "," << this->channel->getLatestVideoDetail();
   }
};
int main(){
    Channel* channel = new Channel("NerdLife");

    Subscriber* sub1 = new Subscriber("Cherrie",channel);
    Subscriber* sub2  = new Subscriber("Aryan",channel);
    channel->Subscribed(sub1);
    channel->Subscribed(sub2);

    channel->UploadNewVideo("Tech Life");
}