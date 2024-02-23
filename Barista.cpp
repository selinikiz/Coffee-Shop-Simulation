#include "Barista.h"
Barista::Barista(int id){ 
    this->id = id;
    freetime = 0; //baristas are free initially
    busytime = 0; //their total busy time is 0 initially
}