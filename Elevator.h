#ifndef _ELEVATOR_H_
#define _ELEVATOR_H_

#include "Assistance.h"

static int countElevator = 0;

class Passenger;
class Building;
class Floor;

class Elevator {
private:
	int capacity;
	int load;
	int floorNumber;
	Building *building;
//	vector<bool> targetFloor;
	int status;//0: 等待 1: 上行 2: 下行
	int elevatorId;
	int countTime;
	int clocker;
	list<Passenger*> passengerList;

	int countTarget();
	void updateStatus();
	void deleteTarget();

public:
    vector<bool> targetFloor;
	Elevator();
	Elevator( Building *building );
	void arriveFloor( int number );
	void leaveFloor( int number );
	int countPassenger();
	int countSpace();
	bool addPassenger( Passenger *passenger );
	bool deletePassenger( Passenger *passenger );
	void clearPassenger();
	int getLoad();
	int getFloorNumber();
	int getStatus();
	void setStatus( int status );
	void setClocker( int time );
	void updateFloor();
	void update();
	void addTarget( int target );
	bool haveTarget( int target );
    int topTarget();
    int bottomTarget();
    void show();
};

#endif