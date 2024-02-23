#include "Customer.h"

Customer::Customer(double ar1, double or1, double br1, double pr1){
    this->firstarrivaltime = ar1; //used later to calculate turnaround time
    this->arrivaltobarista = 0;
    this->arrivaltime = ar1;
    this->ordertime= or1;
    this->brewtime = br1;
    this->price = pr1;
    this->coffeeisdone = 0;
}