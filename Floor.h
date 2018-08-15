#ifndef _FLOOR_H_
#define _FLOOR_H_

#include "Assistance.h"

class Building;
class Elevator;
class Passenger;

class Floor {
private:
	list<Elevator*> elevatorList;
	int floorNumber;
	Building *building;
	deque<Passenger*> upPassengerQueue;
	deque<Passenger*> downPassengerQueue;

public:
//	int num = 1;
    bool button[2];//0=true:上行 1=true:下行
	Floor();
	Floor( int number, Building *building );
	void addElevator( Elevator *elevator );
    bool deleteElevator( Elevator *elevator );
	int countElevator( int status );
	int countPassenger();
	list<Elevator*>* getElevatorList();
	Elevator* findElevator( int status );
//	void updateElevator();
//	void updatePassenger( Passenger &passenger );
	void update();
	deque<Passenger*>* getQueue( int status );
	int getFloorNumber();
	void show();
};

#endif