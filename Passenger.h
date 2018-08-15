#ifndef _PASSENGER_H_
#define _PASSENGER_H_

#include "Assistance.h"

class Building;
class Elevator;
class Floor;

//static int countPassenger = 0;

class Passenger {
private:
//	int passengerId;//乘客编号
	int currentFloor;//当前楼层
	int targetFloor;//目标楼层
	int tolerateTime;//允许等待时间
	int arriveTime;//到达目标楼层的剩余时间
	int workTime;//工作时间
	int status;//-1: 无状态 0: 等待 1: 电梯 2: 步行 3: 工作
	Building *building;//大楼信息
	Elevator *myElevator;//电梯信息

	void initTarget();
	void initTolerate();
	void initWorkTime();

public:
	Passenger();//初始化乘客信息
	Passenger( Building *building );
	bool work();//工作中
	void goToWork();//开始工作
	void walkToTheFloor();//选择步行
	bool walk();//步行
	void appendToQueue( deque<Passenger*> &queue );//进入等待队列
	void leaveQueue( deque<Passenger*> &queue );//离开等待队列
	bool waitElevator();//等待电梯
	Elevator* findElevator( int status, Floor &floor );//查找可乘坐电梯
	void takeElevator( Elevator *elevator );//乘坐电梯
	void quitElevator();//离开电梯
	void update();//更新乘客状态
	void update( Building *building );
	void setBuilding( Building *building );//设置大楼
	int getTargetFloor();//查询当前楼层
	int getStatus();//查询当前状态
	void show();
};

#endif