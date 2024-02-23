// Customer class creates Customers every time order comes, and assign command values to customer's data members.
class Customer{
    public:
        double arrivaltime; //is used to hold the time which customer arrives cashier
        double firstarrivaltime; //is used to hold the time which customer arrives coffeshop
        double ordertime; //is used to hold the time that customer orders
        double brewtime; //is used to hold the time that is needed to make coffee
        double price; //is used to hold price of coffee
        double arrivaltobarista; //is used to hold the time which customer arrives barista (also used to calculate barista's freetime)
        double coffeeisdone; //is used to hold the time which customer takes the coffee (used to calculate turnaround times)
        int customerscashierid; //is used to hold the cashier id that customer went. (used for the 2. design)
        Customer* next;

        Customer(double ar1, double or1, double br1, double pr1);
};