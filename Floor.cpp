#include "Building.h"
#include "Floor.h"
#include "Elevator.h"
#include "Passenger.h"

Floor::Floor() {
    button[0] = false;
    button[1] = false;
    floorNumber = 0;
}

Floor::Floor( int number, Building *building ) {
    button[0] = false;
    button[1] = false;
    floorNumber = number;
    this->building = building;
    building->addFloor(this);
}

// void Floor::enPassenger( Passenger passenger ) {
// 	if(passenger.getTargetFloor() > floorNumber)
// 		upPassengerQueue.push_front(passenger);
// 	else
// 		downPassengerQueue.push_back(passenger)
// }

// void Floor::delPassenger( Passenger &passenger ) {
// 	auto literate
// 	if()
// }

void Floor::addElevator( Elevator *elevator ) {
    if(elevator->countSpace() > 0)
        elevatorList.push_back(elevator);
}

bool Floor::deleteElevator( Elevator *elevator ) {
    for(auto iterator = elevatorList.begin(); iterator != elevatorList.end(); iterator++) {
        if((*iterator) == elevator) {
            elevatorList.erase(iterator);
            return true;
        }
    }
    return false;
}

int Floor::countElevator( int status ) {
    int count = 0;
    for(auto iterator = elevatorList.begin(); iterator != elevatorList.end(); iterator++) {
        if((*iterator)->getStatus() == status && (*iterator)->countSpace() > 0)
            count++;
    }
    return count;
}

int Floor::countPassenger() {
    return static_cast<int>(upPassengerQueue.size() + downPassengerQueue.size());
}

list<Elevator*>* Floor::getElevatorList() {
    return &elevatorList;
}

Elevator* Floor::findElevator( int status ) {
    for(auto iterator = elevatorList.begin(); iterator != elevatorList.end(); iterator++) {
        if((*iterator)->getStatus() == status)
            return *iterator;
    }
    return NULL;
}

//void Floor::updateElevator() {
//	if(!elevatorList.empty()) {
//		for(auto i = elevatorList.begin(); i != elevatorList.end(); i++) {
//			Elevator elevator = *i;
//			if(elevator.getStatus() == 1) {
//				int space = elevator.countSpace();
//				while(space > 0) {
//					auto iterate = upPassengerQueue.end();
//					Passenger passenger = *iterate;
//					upPassengerQueue.pop_back();
//					elevator.addTarget(passenger.getTargetFloor());
//					elevator.addPassenger(passenger);
//					space--;
//				}
//				button[0] = false;
//			} else if(elevator.getStatus() == 2) {
//				int space = elevator.countSpace();
//				while(space > 0) {
//					auto iterate = downPassengerQueue.end();
//					Passenger passenger = *iterate;
//					downPassengerQueue.pop_back();
//					elevator.addTarget(passenger.getTargetFloor());
//					elevator.addPassenger(passenger);
//					space--;
//				}
//				button[1] = false;
//			} else if(elevator.getStatus() == 0) {
//				button[0] = false;
//				button[1] = false;
//			}
//		}
//	}
//}

//void Floor::updatePassenger( Passenger &passenger ) {
//	int flag;
//	if(passenger.getTargetFloor > floorNumber)
//		flag = 1;
//	else if(passenger.getTargetFloor < floorNumber)
//		flag = 2;
//	else
//		flag = 0;
//	if(flag == 0) {
//		passenger.goToWork();
//	} else if(passenger.getStatus() == -1 && passenger.work()) {
//		if(flag == 1)
//			passenger.appendToQueue(upPassengerQueue);
//		else
//			passenger.appendToQueue(downPassengerQueue);
//	} else if(passenger.getStatus() == 0) {
//		Elevator *e = findElevator(flag)
//		if(e != NULL) { //搭乘可用电梯
//
//			passenger.takeElevator();
//			e -> addPassenger(&passenger);
//		} else if(passenger.waitElevator()) { //等待时间结束选择步行
//			if(flag == 1) {
//				passenger.leaveQueue(upPassengerQueue);
//			} else {
//				passenger.leaveQueue(downPassengerQueue);
//			}
//			passenger.walkToTheFloor();
//		}
//	}
//}

void Floor::update() {
    if(countElevator(1) == 0)
        button[0] = false;
    if(!upPassengerQueue.empty() && !button[0]) {
        button[0] = true;
        building->targetElevator(floorNumber, 1);
    }
    if(countElevator(2) == 0)
        button[1] = false;
    if(!downPassengerQueue.empty() && !button[1]) {
        button[1] = true;
        building->targetElevator(floorNumber, 2);
    }
}

deque<Passenger*>* Floor::getQueue( int status ) {
    if(status == 1)
        return &upPassengerQueue;
    else if(status == 2)
        return &downPassengerQueue;
    else
        return NULL;
}

int Floor::getFloorNumber() {
    return floorNumber;
}

void Floor::show() {
    cout <<
    " FloorNumber: " << floorNumber <<
    " ElevatorAmount: " << elevatorList.size() <<
    " UpPassengerAmount: " << upPassengerQueue.size() <<
    " DownPassengerAmount: " << downPassengerQueue.size() <<
    " Up: " << button[0] <<
    " Down " << button[1] <<
    endl;
}
