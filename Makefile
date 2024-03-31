program: Main
	g++ Main.o Barista.o Cashier.o Customer.o Queue.o -o CoffeeShopSimulation
Main: Barista Cashier Customer Queue
	g++ -c Main.cpp -o Main.o
Barista:
	g++ -c Barista.cpp -o Barista.o
Cashier:
	g++ -c Cashier.cpp -o Cashier.o
Customer:
	g++ -c Customer.cpp -o Customer.o
Queue:
	g++ -c Queue.cpp -o Queue.o
