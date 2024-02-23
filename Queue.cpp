#include "Queue.h"
#include <iostream>
using namespace std;

Queue::Queue(){
    front= NULL;
    rear = NULL;
    size = 0;
    maxsize = 0;
}

bool Queue::isEmpty(){
    if (front==NULL && rear ==NULL){
        return true;
    }
    else {
        return false;
    }
}

void Queue::dequeque(){
    if(!isEmpty()){ 
        if (front == rear){
            front = rear = NULL;
        }
        else{
            front = front->next;    
        }
        size--;
    }
}

void CashierQueue::enqueque(Customer* p){
    if (rear == NULL){
        rear = p;
        front = p;
        rear->next = NULL;
    }
    else{
        rear->next = p;
        p->next = NULL;
        rear = p;
    }
    size++;
    if(size>maxsize){
        maxsize = size;
    }
} 

BaristaQueue::BaristaQueue(int id){ //Since BaristaQueues gonna have id, iits constructor is different
    front= NULL;
    rear = NULL;
    size = 0;
    maxsize = 0;
    this->id = id;
}

//BaristaQueue's enqueue method adds customers according to their coffee price. Priority is used. 
void BaristaQueue::enqueque(Customer* p){
    Customer* c = front;
    if (rear == NULL){
        rear = p;
        front = p;
        rear->next = NULL;
    }
    else if( front->price < p->price){
        p->next = front;
        front = p;
    }
    else{ //customer to add has less coffee price than front customer's
        while((c->next!=NULL)&& c->next->price>p->price){ 
            c = c->next;
        } //we will add new customer after c
        if(c->next==NULL){ //that means c is now the rear
            p->next = c->next;
            c->next = p;
            rear = p;
        }
        else{
            p->next = c->next;
            c->next = p;
        }
    }
    size++;
    if(size>maxsize){
        maxsize = size;
    }
}

