#include <iostream>
#include <bits/stdc++.h>
#include "Barista.h"
#include "Cashier.h"
#include "Queue.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cstdlib>
using namespace std;


/* takeorderfromqueue function is called when a customer's arrival time is >= a cashier's free time and there is a queue
* firstly we should take the customers in the queue, this function simply find free cashier for every customer, and make necessary changes
*/
void takeorderfromqueue(int sizeofqueue, CashierQueue* cashierqueue, Cashier* cashierarray[], int cashiernum, double minfreecashier){
    for(int i = 0; i<sizeofqueue; i++){ //turns the whole queue
        minfreecashier = cashierarray[0]->freetime;
        for(int j = 1; j<cashiernum; j++){
            if( cashierarray[j]->freetime<minfreecashier){
                minfreecashier = cashierarray[j]->freetime;
            }
        } //we found the cashier that will be available most early
                
        cashierqueue->front->arrivaltime = minfreecashier; // change the arrival time as the cashier's free time, since customer will arrive when cashier is free
        for(int w = 0; w<cashiernum;w++){
            if(cashierqueue->front->arrivaltime == cashierarray[w]->freetime){ //customer found the ready cashier
                cashierarray[w]->freetime =cashierqueue->front->arrivaltime + cashierqueue->front->ordertime;
                cashierqueue->front->arrivaltobarista = cashierarray[w]->freetime;
                cashierarray[w]->busytime += cashierqueue->front->ordertime;
                cashierqueue->front->customerscashierid = cashierarray[w]->id;
                cashierqueue->dequeque();
                break;
            }
        }
    }
}


/*takeorder function is called for every customer to take order. It searches if there is a free cashier or not.
* if there is a free cashier, it checks whether there is a queue or not, if there is a queue, first take customers from queue.
* if there is no queue, customer directly go to cashier
* if there isn't any free cashier, customer waits in queue
*/
void takeorder(int cashiernum,Customer* cust, Cashier* cashierarray[],CashierQueue* cashierqueue,double minfreecashier){
    int workingcashiers = 0;
    for (int l= 0; l<cashiernum; l++){
        if ((cust->arrivaltime) >= cashierarray[l]->freetime){ //we found a free cashier
            if(cashierqueue->front==NULL){ //there is no cashier queue, customer can directly go to cashier
                cust->customerscashierid = cashierarray[l]->id;
                cashierarray[l]->freetime =cust->arrivaltime + cust->ordertime;
                cust->arrivaltobarista = cashierarray[l]->freetime;
                cashierarray[l]->busytime += cust->ordertime;
                break;
            }
            else{ //there is cashier queue
                takeorderfromqueue(cashierqueue->size,cashierqueue,cashierarray,cashiernum,minfreecashier); //first customers in queue are taken 
                takeorder(cashiernum,cust,cashierarray,cashierqueue,minfreecashier); //and then the customer in the beginning again try to find a free cashier
                break;
            }
        }
        workingcashiers++; //that means customer's arrival time is < cashier's free time
    }
    if(workingcashiers==cashiernum){ //there is no available cashier
        cashierqueue->enqueque(cust);
    } 
}


//findminfreetime function finds the barista that will be free earlier than others
double findminfreetime(Barista* baristaarray[],int baristanum,double minfreebarista){
    minfreebarista = baristaarray[0]->freetime;
    for(int j = 1; j<baristanum; j++){
        if( baristaarray[j]->freetime<minfreebarista){
            minfreebarista = baristaarray[j]->freetime;
        }
    }
    return minfreebarista;
}


/* takeorderfrombaristaqueue function is called to take customers in barista queue, it makes necessary changes for data members
* when the new coming customer's arrival time is bigger than the barista's free time, this function is used to take the customers 
* during that interval
*/
void take_order_from_baristaqueue(BaristaQueue* baristaqueue, Barista* baristaarray[], int baristanum, double minfreebarista){
    baristaqueue->front->arrivaltobarista = minfreebarista;
    for(int w = 0; w<baristanum;w++){
        if(baristaqueue->front->arrivaltobarista == baristaarray[w]->freetime){ //we found the free barista
            baristaarray[w]->freetime =baristaqueue->front->arrivaltobarista + baristaqueue->front->brewtime;
            baristaarray[w]->busytime += baristaqueue->front->brewtime;
            baristaqueue->front->coffeeisdone = baristaarray[w]->freetime;
            baristaqueue->dequeque();
            break;
        }
    }  
}

/* the difference between takeorderfrombaristaqueue and takeorderfrombaristaqueueu2 is, in this function the barista is determined in the design function
*/
void takeorderfrombaristaqueue2(BaristaQueue* baristaqueue,Barista* barista){
    baristaqueue->front->arrivaltobarista = barista->freetime;
    barista->freetime = baristaqueue->front->arrivaltobarista + baristaqueue->front->brewtime;
    barista->busytime += baristaqueue->front->brewtime;
    baristaqueue->front->coffeeisdone = barista->freetime;
    baristaqueue->dequeque();
}


/* brewcoffee function simply makes the same thing as takeorder function, it is called for every customer.
* It searches whether there is a free barista or not. If there is no free barista, customer waits in queue.
* If there is a free barista, then it first checks whether there is a barista queue or not and calls functions according to them
*/
void brewcoffee(int baristanum,Customer* cust, Barista* baristaarray[],BaristaQueue* baristaqueue,double minfreebarista){
    int workingcashiers = 0;
    for (int l= 0; l<baristanum; l++){
        if ((cust->arrivaltobarista) >= baristaarray[l]->freetime){ //we found a free barista
            if(baristaqueue->front==NULL){ //there is no barista queue
                baristaarray[l]->freetime =cust->arrivaltobarista + cust->brewtime;
                baristaarray[l]->busytime += cust->brewtime;
                cust->coffeeisdone = baristaarray[l]->freetime;
                break;
            }
            else{ //there is a barista queue
                minfreebarista = findminfreetime(baristaarray,baristanum,minfreebarista);
                if(cust->arrivaltobarista==baristaarray[l]->freetime){
                    baristaqueue->enqueque(cust);
                    take_order_from_baristaqueue(baristaqueue,baristaarray,baristanum,minfreebarista);
                    break;
                }
                else{
                    while (cust->arrivaltobarista>minfreebarista){ //first we should take customers in queue in the time interval of this customer hadn't arrived yet
                        take_order_from_baristaqueue(baristaqueue,baristaarray,baristanum,minfreebarista);
                        minfreebarista = findminfreetime(baristaarray,baristanum,minfreebarista);
                    }
                    brewcoffee(baristanum,cust,baristaarray,baristaqueue,minfreebarista); //after taking customers from queue, we again check whether any barista is free or not
                    break;
                }
            }
        }
        workingcashiers++;
    }
    if(workingcashiers==baristanum){ //that means there is no free barista
        baristaqueue->enqueque(cust);
    } 
}

/* the difference between brecoffee and brewcoffee2 is, in this function the barista is determined in the design function
*/
void brewcoffee2(Customer* cust,Barista* barista,BaristaQueue* baristaqueue){
    if ((cust->arrivaltobarista) >= barista->freetime){ //if the barista is free
        if(baristaqueue->front==NULL){ //if there is no queue, it directly goes to barista
            barista->freetime =cust->arrivaltobarista + cust->brewtime;
            barista->busytime += cust->brewtime;
            cust->coffeeisdone =barista->freetime;
        }
        else{ //if there is a queue
            if(cust->arrivaltobarista == barista->freetime){
                baristaqueue->enqueque(cust);
                takeorderfrombaristaqueue2(baristaqueue,barista);
            }
            else{
                while (cust->arrivaltobarista>barista->freetime){
                    takeorderfrombaristaqueue2(baristaqueue,barista);
                }
                brewcoffee2(cust,barista,baristaqueue); 
            }
        }
    }
    else{ //if barista is not free, waits in queue
        baristaqueue->enqueque(cust);
    }
}
bool compareCustomers(Customer* c1, Customer* c2){
    return (c1->arrivaltobarista< c2->arrivaltobarista);
}

//this function is used for delete everything
void delete_everything(int design,BaristaQueue* baristaqueuesarray[], CashierQueue* cashierqueue, Cashier* cashierarray[], Barista* baristaarray[], Customer* customerarray[],int cashiernum,int baristanum,int orders){
    delete cashierqueue;
    for (int i=0;i<cashiernum;i++){
        delete cashierarray[i];
    }
    for (int i=0;i<baristanum;i++){
        delete baristaarray[i];
    }
    for (int i=0;i<orders;i++){
        delete customerarray[i];
    }
    if(design == 1){
        delete baristaqueuesarray[0];
    }
    else{
        for( int i =0 ; i< baristanum;i++ ){
            delete baristaqueuesarray[i];
        }
    }
}


/* design1 function implements model 1. Starts from the beginning, creates new customers, call functions for sending customers to cashiers and 
* then baristas. At the end prints all
*/
void design1(FILE *outputfile, fstream* myfile, string line, int baristanum,int cashiernum,int orders){  
    
    // ----------------------------------- NECESSARY INITIALIZATIONS -----------------------------------
    int numcustomer = 0; //it will be used to hold customers in an array
    double minfreecashier; //it represents minimum free time of cashier
    double minfreebarista; //it represents minimum free time of barista
    double totalrunningtime;
    CashierQueue* cashierqueue = new CashierQueue;
    
    Cashier* cashierarray[cashiernum]; 
    for (int k= 0; k<cashiernum;k++){
        cashierarray[k] = new Cashier(k+1); //constructor is used to hold cashier id
    } //cashierarray is filled with cashiers
    
    Barista* baristaarray[baristanum];
    for (int po = 0; po< baristanum;po++){
        baristaarray[po] = new Barista(po+1); //constructor is used to hold barista id
    } //baristaarray is filled with baristas
    
    Customer* customerstobarista[orders];
    Customer* customerarray[orders]; //this array is used later to print customer turnaround times 
    //BaristaQueue* beforegoingbarista = new BaristaQueue(1);
    
    while(getline(*myfile,line)){
        double commands[4]; 
        stringstream ss(line);
        string word;
        int i = 0;
        while (ss>>word) {
            commands[i] = atof(word.c_str()); 
            i++;
        } //commands array holds arrival time, order time, brew time, price respectively
        Customer* cust1 = new Customer(commands[0],commands[1],commands[2],commands[3]);
        //beforegoingbarista->enqueque2(cust1);
        customerstobarista[numcustomer] = cust1;
        customerarray[numcustomer] = cust1;
        numcustomer++;
    }
    
    // ----------------------------------- CUSTOMER ORDER TIME -----------------------------------
    for (int i= 0; i< orders; i++){
        //for every customer takeorder function is called, 
        takeorder(cashiernum,customerarray[i],cashierarray,cashierqueue,minfreecashier);
    }
    /* if last customer is send to cashier queue, that means customer are still waiting in queue, so after calling takeorder
    * function for every customer, we should check if there is a queue or not
    */
    if(cashierqueue->front!=NULL){ 
        int sizeofqueue= cashierqueue->size;
        takeorderfromqueue(sizeofqueue,cashierqueue,cashierarray,cashiernum,minfreecashier);  //take customers in the queue
    }
    sort(customerstobarista,customerstobarista+orders,compareCustomers);

    // ----------------------------------- CUSTOMER BREW TIME -----------------------------------
    BaristaQueue* baristaqueuesarray[baristanum]; // it is just used to have same function for model1 and model2 for deletion
    BaristaQueue* baristaqueue = new BaristaQueue(1);
    baristaqueuesarray[0] = baristaqueue;

    int o= 0;
    while(o< orders){//make appropriate changes for customers during brew time
        brewcoffee(baristanum,customerstobarista[o],baristaarray,baristaqueue,minfreebarista);
        o++;
    }
    /* if last customer is send to barista queue, that means customer are still waiting in queue, so after calling brewcoffee
    * function for every customer, we should check if there is a queue or not
    */
    if(baristaqueue->front!=NULL){
        while(baristaqueue->front!=NULL){
            minfreebarista = findminfreetime(baristaarray,baristanum,minfreebarista);
            take_order_from_baristaqueue(baristaqueue,baristaarray,baristanum,minfreebarista);   //take customers in the queue
        }
    }

    // ----------------------------------- PRINT EVERYTHING -----------------------------------
    totalrunningtime = baristaarray[0]->freetime;
    for(int i = 0; i<baristanum;i++){
        if(baristaarray[i]->freetime> totalrunningtime){
            totalrunningtime = baristaarray[i]->freetime;
        }
    }
    fprintf(outputfile,"%.2lf\n", totalrunningtime);
    fprintf(outputfile,"%u\n",cashierqueue->maxsize);
    fprintf(outputfile,"%u\n",baristaqueue->maxsize);
    for(int i= 0; i<cashiernum;i++){
        fprintf(outputfile,"%.2lf\n", cashierarray[i]->busytime/totalrunningtime);
    }
    for(int i= 0; i<baristanum;i++){
        fprintf(outputfile,"%.2lf\n", baristaarray[i]->busytime/totalrunningtime);
    }
    for(int i = 0; i<orders;i++){
        fprintf(outputfile,"%.2lf\n", customerarray[i]->coffeeisdone-customerarray[i]->firstarrivaltime);
    }

    delete_everything(1,baristaqueuesarray,cashierqueue,cashierarray,baristaarray,customerarray,cashiernum,baristanum,orders);
    
}


/* design2 function implements model 2. Starts from the beginning, creates new customers, call functions for sending customers to cashiers and 
* then baristas. At the end prints all
*/
void design2(FILE *outputfile, fstream* myfile, string line, int baristanum,int cashiernum,int orders){
    
    // ----------------------------------- NECESSARY INITIALIZATIONS -----------------------------------
    int numcustomer2 = 0; //it will be used to hold customers in an array
    double minfreecashier2; //it represents minimum free time of cashier
    double minfreebarista2; //it represents minimum free time of barista
    double totalrunningtime2;
    CashierQueue* cashierqueue2 = new CashierQueue;
    
    Cashier* cashierarray2[cashiernum]; 
    for (int k= 0; k<cashiernum;k++){
        cashierarray2[k] = new Cashier(k+1); //constructor is used to hold cashier id
    } //cashierarray is filled with cashiers
    
    Barista* baristaarray2[baristanum];
    for (int po = 0; po< baristanum;po++){
        baristaarray2[po] = new Barista(po+1); //constructor is used to hold barista id
    } //baristaarray is filled with baristas
    
    Customer* customerstobarista2[orders]; 
    Customer* customerarray2[orders]; //this array is used later to print customer turnaround times 
    
    while(getline(*myfile,line)){
        double commands[4]; 
        stringstream ss(line);
        string word;
        int i = 0;
        while (ss>>word) {
            commands[i] = atof(word.c_str()); 
            i++;
        } //commands array holds arrival time, order time, brew time, price respectively
        Customer* cust2 = new Customer(commands[0],commands[1],commands[2],commands[3]);
        customerstobarista2[numcustomer2] = cust2;
        customerarray2[numcustomer2] = cust2;
        numcustomer2++;
    }
    // ----------------------------------- CUSTOMER ORDER TIME -----------------------------------
    for (int i= 0; i< orders; i++){
        takeorder(cashiernum,customerarray2[i],cashierarray2,cashierqueue2,minfreecashier2);
    }
    /* if last customer is send to cashier queue, that means customer are still waiting in queue, so after calling takeorder
    * function for every customer, we should check if there is a queue or not
    */
    if(cashierqueue2->front!=NULL){
        int sizeofqueue= cashierqueue2->size;
        takeorderfromqueue(sizeofqueue,cashierqueue2,cashierarray2,cashiernum,minfreecashier2);   
    }
    sort(customerstobarista2,customerstobarista2+orders,compareCustomers);

    // ----------------------------------- CUSTOMER BREW TIME -----------------------------------
    BaristaQueue* baristaqueuesarray2[baristanum]; //to print all the barista queues max size's later
    for (int i= 0; i<baristanum;i++){
        baristaqueuesarray2[i] = new BaristaQueue(i+1);
    }
    int o= 0;
    while(o<orders){
        BaristaQueue* baristaqueuetosend; // which barista queue should customer go
        Barista* baristatosend;// which barista should customer go
        for(int i= 0; i<baristanum;i++){
            if((customerstobarista2[o]->customerscashierid/3.0)<=baristaqueuesarray2[i]->id){
                baristaqueuetosend = baristaqueuesarray2[i];
                break;
            }
        }
        for ( int i= 0; i<baristanum; i++){
            if((customerstobarista2[o]->customerscashierid/3.0)<=baristaarray2[i]->id){
                baristatosend = baristaarray2[i];
                break;
            }
        }
        brewcoffee2(customerstobarista2[o],baristatosend,baristaqueuetosend);
        o++;
    }
    /* if last customer is send to barista queue, that means customer are still waiting in queue, so after calling brewcoffee2
    * function for every customer, we should check if there is any queue or not
    */
    for(int i= 0; i<baristanum;i++){
        if(baristaqueuesarray2[i]->front!=NULL){
            while(baristaqueuesarray2[i]->front!=NULL){
                takeorderfrombaristaqueue2(baristaqueuesarray2[i],baristaarray2[i]); 
            }
        }
    }

    // ----------------------------------- PRINT EVERYTHING -----------------------------------
    totalrunningtime2 = baristaarray2[0]->freetime;
    for(int i = 0; i<baristanum;i++){
        if(baristaarray2[i]->freetime> totalrunningtime2){
            totalrunningtime2 = baristaarray2[i]->freetime;
        }
    }
    fprintf(outputfile,"%.2lf\n", totalrunningtime2);
    fprintf(outputfile,"%u\n",cashierqueue2->maxsize);
    for(int i= 0; i<baristanum; i++){
        fprintf(outputfile,"%u\n",baristaqueuesarray2[i]->maxsize);
    }
    for(int i= 0; i<cashiernum;i++){
        fprintf(outputfile,"%.2lf\n", cashierarray2[i]->busytime/totalrunningtime2);
    }
    for(int i= 0; i<baristanum;i++){
        fprintf(outputfile,"%.2lf\n", baristaarray2[i]->busytime/totalrunningtime2);
    }
    for(int i = 0; i<orders;i++){
        fprintf(outputfile,"%.2lf", customerarray2[i]->coffeeisdone-customerarray2[i]->firstarrivaltime);
        if(i == orders-1){
        }
        else{
            fprintf(outputfile,"\n");
        }
    }
    delete_everything(2,baristaqueuesarray2,cashierqueue2,cashierarray2,baristaarray2,customerarray2,cashiernum,baristanum,orders);
}


int main(int argc, char *argv[]){
    int cashiernum;
    int baristanum;
    int orders;
    string line;
    fstream myfile;
    myfile.open(argv[1],ios::in);
    FILE *outputfile = fopen(argv[2],"w");
    if (getline(myfile, line)){ 
        cashiernum = atoi(line.c_str());
    }
    baristanum = cashiernum /3;
    if (getline(myfile, line)){ 
        orders = atoi(line.c_str());
    }
    design1(outputfile,&myfile,line,baristanum,cashiernum,orders);
    myfile.close();
    fprintf(outputfile,"\n");

    //read the file again for second design
    string line2;
    fstream myfile2;
    myfile2.open(argv[1],ios::in);
    if (getline(myfile2, line)){ 
        cashiernum = atoi(line.c_str());
    }
    baristanum = cashiernum /3;
    if (getline(myfile2, line)){ 
        orders = atoi(line.c_str());
    }
    design2(outputfile,&myfile2,line2,baristanum,cashiernum,orders);
    myfile2.close();
    fclose(outputfile);

    return 0;
}