taxi.out: TaxiMain.o Taxi.o Graph.o Dispatcher.o 
	g++ -o taxi.out TaxiMain.o Taxi.o Graph.o Dispatcher.o

TaxiMain.o: TaxiMain.cpp Dispatcher.h
	g++ -c TaxiMain.cpp

Dispatcher.o: Dispatcher.cpp Dispatcher.h Taxi.h
	g++ -c Dispatcher.cpp

Taxi.o: Taxi.cpp Taxi.h 
	g++ -c Taxi.cpp

Graph: Graph.cpp Graph.h
	g++ -c Graph.cpp