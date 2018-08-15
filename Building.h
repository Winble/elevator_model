#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "Assistance.h"

class Floor;
class Elevator;
class Passenger;

class Building{
private:


public:
    vector<Floor*> floorList;
    vector<Elevator*> elevatorList;
    vector<Passenger*> passengerList;
//    Building();
//    void createFloor();
//    void createElevator();
//    void createPassenger();
	void addFloor( Floor *floor );//新建楼层
	void addElevator( Elevator *elevator );//新建电梯
	void addPassenger( Passenger *passenger );//新建乘客
	int getHeight();//楼层高度
	Floor* findFloor(int floorNumber);//查找楼层
	void targetElevator( int floorNumber, int status );//根据楼层开关调度电梯
	void update();
	void show();
	void run(int times);
};

#endif