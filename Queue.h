#include "Customer.h"
#include <iostream>
using namespace std;

// Queue class is used to create a queue for customers. Inheritance is used for cashier and barista queue
class Queue{
    public:
        int id; //used to hold barista queue id's for design 2
        Customer* front;
        Customer* rear;
        int size;
        int maxsize; 
    
    Queue();
    bool isEmpty(); 
    void dequeque(); //dequeue method is same for CashierQueue and BaristaQueue
};

class CashierQueue: public Queue{
    public:
    void enqueque(Customer* p);
};

class BaristaQueue: public Queue{
    public:
    BaristaQueue(int id);
    void enqueque(Customer* p);
};