#include "Cashier.h"
Cashier::Cashier(int id){ 
    this->id = id;
    freetime = 0; //cashiers are free initially
    busytime = 0; //their total busy time is 0 initially
}