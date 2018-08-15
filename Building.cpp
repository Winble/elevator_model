#include "Building.h"
#include "Floor.h"
#include "Elevator.h"
#include "Passenger.h"

void Building::addFloor(Floor *floor) {
    floorList.push_back(floor);
}

void Building::addElevator(Elevator *elevator) {
    elevatorList.push_back(elevator);
}

void Building::addPassenger(Passenger *passenger) {
    passengerList.push_back(passenger);
}

int Building::getHeight() {
    return floorList.size();
}

Floor* Building::findFloor(int floorNumber) {
//    for(auto iterator = floorList.begin(); iterator != floorList.end(); iterator++) {
//        if((*iterator)->getFloorNumber() == floorNumber)
//            return *iterator;
//    }
    if(floorNumber > floorList.size() - 1 || floorNumber < 0)
        return NULL;
    return floorList[floorNumber];
}

void Building::targetElevator( int floorNumber, int status ) {//电梯调度
//    //查找是否有停靠在本层或目前运行方向上将要经过本层的电梯
//    for(auto iterator = elevatorList.begin(); iterator != elevatorList.end(); iterator++) {
//        if((*iterator)->haveTarget(floorNumber) && (*iterator)->countSpace() > 0) {
//            if((*iterator)->getFloorNumber() == floorNumber && (*iterator)->getStatus() == 0) {
//                //电梯在本层
//                (*iterator)->setStatus(status);
//                return;
//            } else {
//                //判断是否在运行方向上将要进过本层
//                if((status == 1 && (*iterator)->getStatus() == 1 && (*iterator)->getFloorNumber() < floorNumber)
//                || (status == 2 && (*iterator)->getStatus() == 2 && (*iterator)->getFloorNumber() > floorNumber)) {
//                    (*iterator)->addTarget(floorNumber);
//                    return;
//                }
//            }
//        }
//    }
//    //调度正在运行或等待状态的最近电梯
//    int count = 0;
//    int elevatorNumber = -1;
//    int scope = static_cast<int>(floorList.size());
//    for(auto iterator = elevatorList.begin(); iterator != elevatorList.end(); iterator++) {
//        int nearestFloor;
//        Elevator &elevator = **iterator;
//        if(elevator.getStatus() == 0)
//            nearestFloor = floorNumber;
//        else {
//            if(abs(elevator.topTarget() - floorNumber) < abs(elevator.bottomTarget() - floorNumber))
//                nearestFloor = elevator.topTarget();
//            else
//                nearestFloor = elevator.bottomTarget();
//        }
//        if(abs(floorNumber - nearestFloor) < scope)
//            elevatorNumber = count;
//        count ++;
//    }
//    elevatorList[elevatorNumber]->addTarget(floorNumber);
    //查找当前楼层停靠的电梯
    Elevator *elevator = findFloor(floorNumber)->findElevator(0);
    if(elevator != NULL) {
        elevator->setStatus(status);
        return;
    }
    //根据楼层的指示灯上行则向下查找电梯，下行则向上查找电梯直到找到运行方向相同的电梯在上方的反方向电梯
    if(status == 1) {
        for(int i = floorNumber - 1; i != -1; i--) {
            for(int j = 0; j < elevatorList.size(); j++) {
                elevator = elevatorList.at(j);
                if(elevator->getStatus() != 2) {
                    elevator->addTarget(floorNumber);
                    return;
                }
            }
        }
        for(int i = floorNumber + 1; i != floorList.size(); i++) {
            for(int j = 0; j < elevatorList.size(); j++) {
                elevator = elevatorList.at(j);
                if(elevator->getStatus() != 1) {
                    elevator->addTarget(floorNumber);
                    return;
                }
            }
        }
    } else if(status == 2) {
        for(int i = floorNumber + 1; i != floorList.size(); i++) {
            for(int j = 0; j < elevatorList.size(); j++) {
                elevator = elevatorList.at(j);
                if(elevator->getStatus() != 1) {
                    elevator->addTarget(floorNumber);
                    return;
                }
            }
        }
        for(int i = floorNumber - 1; i != -1; i--) {
            for(int j = 0; j < elevatorList.size(); j++) {
                elevator = elevatorList.at(j);
                if(elevator->getStatus() != 2) {
                    elevator->addTarget(floorNumber);
                    return;
                }
            }
        }
    }
}

void Building::update() {
    for(auto iterator = floorList.begin(); iterator != floorList.end(); iterator++)
        (*iterator)->update();
    for(auto iterator = passengerList.begin(); iterator != passengerList.end(); iterator++)
        (*iterator)->update();
    for(auto iterator = elevatorList.begin(); iterator != elevatorList.end(); iterator++)
        (*iterator)->update();
}

void Building::show() {
    cout << "================================================================================" << endl;
    cout << " FloorList" << endl;
    for(auto &iterator : floorList)
        iterator->show();
    cout << " ElevatorList" << endl;
    for(auto &iterator : elevatorList)
        iterator->show();
}

void Building::run(int times) {
    for(int k = 0; k < times; k++) {
        update();
        cout << "---------";
        for(int i = 0; i < elevatorList.size(); i++)
            cout << "------";
        cout << endl;
        cout << left << setw(9) << " Floor";
        for(int i = 0; i < elevatorList.size(); i++) {
            cout << " ";
            cout << setw(2) << right << elevatorList[i]->getFloorNumber();
            cout << "   ";
        }
        cout << endl;
        for(int i = static_cast<int>(floorList.size() - 1); i >= 0; i--) {
            Floor &floor = *floorList[i];
            cout << right << setw(2) << i << ":";
            if(floor.button[0])
                cout << "U";
            else cout << "-";
            if(floor.button[1])
                cout << "D";
            else cout << "-";
            cout << left << setw(3) << floor.countPassenger();
            cout << " ";
            for(int j = 0; j < elevatorList.size(); j++) {
                if(elevatorList[j]->getFloorNumber() == floor.getFloorNumber()) {
                    if(elevatorList[j]->getStatus() == 0)
                        cout << "Wt";
                    else if(elevatorList[j]->getStatus() == 1)
                        cout << "Up";
                    else cout << "Dn";
                    cout << ":" << left << setw(2) << elevatorList[j]->countPassenger();
                } else {
                    cout << "     ";
                }
                cout << " ";
            }
            cout << endl;
        }
        cout << "---------";
        for(int i = 0; i < elevatorList.size(); i++)
            cout << "------";
        cout << endl;
    }
}