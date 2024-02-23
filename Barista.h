//Barista class is used to create Barista objects. 
class Barista{
    public: 
        double freetime; //is used to hold the time when the barista is free.
        double busytime; //is used to hold the total time that barista worked
        int id; //is used for their id, it is used later for deciding which customer goes which barista.
 
        Barista(int id);
};