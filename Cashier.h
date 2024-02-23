/* Cashier class is used for the Cashier objects. 'freetime' is used to hold the time when the cashier is free.
* 'busytime' is used to hold the total time that cashier worked
* 'id' is used for their id, it is used later for deciding which customer goes which cashier.
*/
class Cashier{
    public: 
        double freetime;
        double busytime;
        int id;
 
        Cashier(int id);
};