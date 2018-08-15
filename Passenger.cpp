#include "Passenger.h"
#include "Building.h"
#include "Floor.h"
#include "Elevator.h"

void Passenger::initTarget() {
    targetFloor = rand() % building->getHeight();
}

void Passenger::initTolerate() {
    tolerateTime = (targetFloor - currentFloor) * (climbSpeed - elevatorSpeed);
}

void Passenger::initWorkTime() {
    workTime = rand() % 29 + 40;
}

Passenger::Passenger() {
//    passengerId = countPassenger++;
    currentFloor = 0;
    arriveTime = -1;
    workTime = 0;
    status = -1;
}

Passenger::Passenger( Building *building ) {
//    passengerId = countPassenger++;
    currentFloor = 0;
    targetFloor = -1;
    arriveTime = -1;
    workTime = 0;
    status = -1;
    this->building = building;
    building->addPassenger(this);
}

bool Passenger::work() {
    if(workTime > 0) {
        workTime--;
        return false;
    } else {
        initTarget();
        initTolerate();
        status = -1;
        return true;// 工作结束
    }
}

void Passenger::goToWork() {
    status = 3;
    targetFloor = -1;
    initWorkTime();
}

void Passenger::walkToTheFloor() {
    status = 2;
    arriveTime = abs((targetFloor - currentFloor)) * climbSpeed;
    currentFloor = -1;
    tolerateTime = 0;
}

bool Passenger::walk() {
    if(arriveTime <= 0) {
        status = -1;
        currentFloor = targetFloor;
        targetFloor = -1;
        arriveTime = -1;
        return true;
    }
    arriveTime--;
    return false;
}

void Passenger::appendToQueue( deque<Passenger*> &queue ) {
    status = 0;//等待电梯
    initTolerate();
    queue.push_front(this);
}

void Passenger::leaveQueue( deque<Passenger*> &queue ) {
    status = -1;
    for(auto iterator = queue.begin(); iterator != queue.end(); iterator++) {
        if((*iterator) == this) {
            queue.erase(iterator);
            break;
        }
    }
}

bool Passenger::waitElevator() {
    if(tolerateTime > 0) {
        tolerateTime --;
        return false;
    } else {
        return true;//结束等待
    }
}

Elevator* Passenger::findElevator( int status, Floor &floor ) {
    auto &queue = *floor.getQueue(status);
    int order = 0;
    auto &elevatorList = *floor.getElevatorList();
    for(auto iterator = queue.begin(); iterator != queue.end(); iterator++) {
        if((*iterator) == this)
            break;
        order++;
    }
    for(auto iterator = elevatorList.begin(); iterator != elevatorList.end(); iterator++) {
        auto &i = *iterator;
        if(i->getStatus() == status && i->countSpace() > order)
            return i;
    }
    return NULL;
}

void Passenger::takeElevator( Elevator *elevator ) {
    status = 1;
    arriveTime = abs((targetFloor - currentFloor)) * elevatorSpeed - 1;
    currentFloor = -1;
    tolerateTime = 0;
    elevator->addPassenger(this);
    myElevator = elevator;
    elevator->addTarget(targetFloor);
}

void Passenger::quitElevator() {
    status = -1;
    arriveTime = -1;
    currentFloor = myElevator->getFloorNumber();
    targetFloor = -1;
    myElevator->deletePassenger(this);
    myElevator = NULL;
}

void Passenger::update() {
    if(targetFloor == -1 && !work()) { //处于工作状态
        return;
    }
    int flag;
    if(targetFloor > currentFloor)
        flag = 1;
    else if(targetFloor < currentFloor)
        flag = 2;
    else
        flag = 0;
    if(flag == 0) { //目标楼层与当前楼层相等
        goToWork();
        return;
    }
    Floor &floor = *building->findFloor(currentFloor);
    if(status == -1) {
        appendToQueue(*floor.getQueue(flag));
    } else if(status == 0) {
        Elevator *e = findElevator(flag, floor);
        if(e != NULL) { //搭乘可用电梯
            leaveQueue(*floor.getQueue(flag));
            takeElevator(e);
        } else if(waitElevator()) { //等待时间结束选择步行
            leaveQueue(*floor.getQueue(flag));
            walkToTheFloor();
        }
    } else if(status == 1) { //在电梯上
        if(arriveTime == 1) {
            arriveTime--;
            quitElevator();
            goToWork();
        } else if(myElevator->getFloorNumber() != targetFloor)
            arriveTime--;
//        else {
//            quitElevator();
//            goToWork();
//        }
    } else if(status == 2) { //在步行
        if(walk())//步行结束
            goToWork();
    }
}

void Passenger::update( Building *building ) {
    setBuilding(building);
    update();
}

void Passenger::setBuilding( Building *building ) {
    this->building = building;
}

int Passenger::getTargetFloor() {
    return targetFloor;
}

int Passenger::getStatus() {
    return status;
}

void Passenger::show() {
    cout <<
    " currentFloor: " << currentFloor <<
    " targetFloor: " << targetFloor <<
    " tolerateTime: " << tolerateTime <<
    " arriveTime: " << arriveTime <<
    " workTime: " << workTime <<
    " status: " << status <<
    endl;
}