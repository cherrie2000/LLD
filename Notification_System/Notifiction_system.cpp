#include<bits/stdc++.h>
using namespace std;

class INotification{
    public:
    virtual string getContent() const =0;
    virtual  ~INotification() {};
};

class SimpleNotification:public INotification{
    string text;
    public:

    SimpleNotification(string s){
        text =s;
    }

    string getContent() const override{
        return text;
    }
};

//Abstract Decorator wraps a notification object

class INotificationDecorator: public INotification{
    protected:
    INotification* n;
    public:
    INotificationDecorator(INotification* notif){
        n =notif;
    }
    virtual ~INotificationDecorator(){
        delete n;
    }
};

class TimeStampDecorator: public INotificationDecorator{
    public:
    TimeStampDecorator(INotification* n):INotificationDecorator(n){}

    string getContent() const override{
        return "[2025-04-13 14:22:00] " + n->getContent();
    }
};

class SignatureDecorator: public INotificationDecorator{
    private:
    string signature;
    public:
    SignatureDecorator(string s, INotification*n):INotificationDecorator(n){signature =s;}
    string getContent() const override {
        return n->getContent() + "\n-- " + signature + "\n\n";
    }
};

//Observer design Pattern
class IObserver{
    public:
    virtual void update()=0;
    virtual ~IObserver(){};
} ;

class IObservable{
    public:
    virtual void addObserver(IObserver* observer)=0;
    virtual void removeObserver(IObserver* observer)=0;
    virtual void notify()=0;

    virtual ~IObservable(){};
};

class NotifyObservable:public IObservable{
    private:
    vector<IObserver*> observes;
    INotification* current_notification;

    public:
    void addObserver(IObserver* observer) override{
        observes.push_back(observer);
    }
    void removeObserver(IObserver* observer) override{
        auto it = find(observes.begin(),observes.end(),observer);
        observes.erase(it);
    }    
    void notify() override{
        for(auto it:observes){
            it->update();
        }
    }
    void setNotification(INotification* notif){
        if(current_notification!=nullptr){
            delete current_notification;
        }
        current_notification = notif;
        notify();
    }
    INotification* getNotification(){
        return current_notification;
    }
    string getNotificationContent(){
        return current_notification->getContent();
    }

        ~NotifyObservable() {
        if (current_notification != NULL) {
            delete current_notification;
        }
    }
};

//Concrete Observer 1
class Logger: public IObserver{
    private:
    NotifyObservable* notification;

    public:
    Logger(NotifyObservable* n){
        notification=n;
    }
    void update() override{
        cout<< "Logging New Notification : \n" << notification->getNotificationContent();
    }
};

//Strategy Pattern
class INotificationStrategy{
    public:
    virtual void sendNotification(string content) =0;
    virtual ~INotificationStrategy(){};
};

class EmailStrategy : public INotificationStrategy {
private:
    string emailId;
public:

    EmailStrategy(string emailId) {
        this->emailId = emailId;
    }

    void sendNotification(string content) override {
        // Simulate the process of sending an email notification, 
        // representing the dispatch of messages to users via email.​
        cout << "Sending email Notification to: " << emailId << "\n" << content;
    }
};

class SMSStrategy : public INotificationStrategy {
private:
    string mobileNumber;
public:

    SMSStrategy(string mobileNumber) {
        this->mobileNumber = mobileNumber;
    }

    void sendNotification(string content) override {
        // Simulate the process of sending an SMS notification, 
        // representing the dispatch of messages to users via SMS.​
        cout << "Sending SMS Notification to: " << mobileNumber << "\n" << content;
    }
};

class PopUpStrategy : public INotificationStrategy {
public:
    void sendNotification(string content) override {
        // Simulate the process of sending popup notification.
        cout << "Sending Popup Notification: \n" << content;
    }
};



class NotificationEngine: public IObserver{
    private:
    NotifyObservable* notif;
    vector<INotificationStrategy*> strategies;
    public:
    NotificationEngine(NotifyObservable* n){
        notif = n;
    }
    void addNotificationStrategy(INotificationStrategy* notification){
        strategies.push_back(notification);
    }
    void update(){
        string message = notif->getNotificationContent();
        for(auto it:strategies){
            it->sendNotification(message);
        }
    }
};

class NotificationService{
    private:
     static NotificationService* instance;
    vector<INotification*> notifications;
    NotifyObservable* observable;

    NotificationService(){
        observable = new NotifyObservable();
    }
    public:

    static NotificationService* getInstance(){
        if(instance==nullptr){
            return new NotificationService();;
        }
        return instance;
    }
    void sendNotification(INotification* notification) {
        notifications.push_back(notification); // history
        observable->setNotification(notification);
    }
    NotifyObservable* getObservable() {
        return observable;
    }
    ~NotificationService() {
        delete observable;
    }
};
NotificationService* NotificationService::instance = nullptr;


int main() {
    // Create NotificationService.
    NotificationService* notificationService = NotificationService::getInstance();

    // Get Observable
    NotifyObservable* notificationObservable = notificationService->getObservable();
   
    // Create Logger Observer
    Logger* logger = new Logger(notificationObservable);

    // Create NotificationEngine observers.
    NotificationEngine* notificationEngine = new NotificationEngine(notificationObservable);

    notificationEngine->addNotificationStrategy(new EmailStrategy("random.person@gmail.com"));
    notificationEngine->addNotificationStrategy(new SMSStrategy("+91 9876543210"));
    notificationEngine->addNotificationStrategy(new PopUpStrategy());

    // Attach these observers.
    notificationObservable->addObserver(logger);
    notificationObservable->addObserver(notificationEngine);

    // Create a notification with decorators.
    INotification* notification = new SimpleNotification("Your order has been shipped!");
    notification = new TimeStampDecorator(notification);
    notification = new SignatureDecorator("Customer Care",notification);
    
    notificationService->sendNotification(notification);

    delete logger;
    delete notificationEngine;
    return 0;
}