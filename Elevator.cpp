#include "Building.h"
#include "Floor.h"
#include "Elevator.h"
#include "Passenger.h"

Elevator::Elevator() {
    capacity = elevatorCapacity;
    load = 0;
    floorNumber = 0;
    status = 0;
    elevatorId = countElevator++;
}

Elevator::Elevator( Building *building ) {
    capacity = elevatorCapacity;
    load = 0;
    floorNumber = 0;
    status = 0;
    elevatorId = countElevator++;
    for(int i = 0; i < building->getHeight(); i++)
        targetFloor.push_back(false);
    this->building = building;
    arriveFloor(0);
    building->addElevator(this);
    clocker = 0;
}

void Elevator::arriveFloor(int number) {
    Floor *floor = building->findFloor(number);
    floor->addElevator(this);
    deleteTarget();
}

void Elevator::leaveFloor(int number) {
    Floor *floor = building->findFloor(number);
    floor->deleteElevator(this);
}

int Elevator::countPassenger() {
    return load;
}

int Elevator::countSpace() {
    if(clocker == 0 && status != 0) {
        int out = 0;
        for(auto iterator = passengerList.begin(); iterator != passengerList.end(); iterator++) {
            if((*iterator)->getTargetFloor() == floorNumber)
                out++;
        }
        return capacity - load + out;
    }
    return capacity - load;
}

bool Elevator::addPassenger(Passenger *passenger) {
    if(load < capacity) {
        passengerList.push_back(passenger);
        load++;
        return true;
    }
    return false;
}

bool Elevator::deletePassenger(Passenger *passenger) {
    for(auto iterate = passengerList.begin(); iterate != passengerList.end(); iterate++) {
        if((*iterate) == passenger) {
            passengerList.erase(iterate);
            load--;
            return true;
        }
    }
    return false;
}

void Elevator::clearPassenger() {
    if(load > 0) {
        auto iterate = passengerList.begin();
        while(iterate != passengerList.end()) {
            if((*iterate)->getTargetFloor() == floorNumber) {
                iterate = passengerList.erase(iterate);
                load--;
            } else {
                iterate++;
            }
        }
    }
}

int Elevator::getLoad() {
    return load;
}

int Elevator::getFloorNumber() {
    return floorNumber;
}

int Elevator::getStatus() {
    return status;
}

void Elevator::setStatus( int status ) {
    this->status = status;
}

void Elevator::setClocker(int time) {
    clocker = time;
}

int Elevator::countTarget() {
    int count = 0;
    for(int i = 0; i < building->getHeight(); i++) {
        if(targetFloor[i])
            count++;
    }
    return count;
}

int Elevator::topTarget() {
    int i;
    for(i = building->getHeight() - 1; i != floorNumber; i--) {
        if(targetFloor.at(i))
            break;
    }
    return i;
}

int Elevator::bottomTarget() {
    int i;
    for(i = 0; i != floorNumber; i++) {
        if(targetFloor.at(i))
            break;
    }
    return i;
}

void Elevator::updateStatus() {
    if(countTarget() == 0) {
        status = 0;
    } else {
        int top = topTarget();
        int bottom = bottomTarget();
        if(status == 1 && floorNumber == top) {
            status = 2;
        } else if(status == 2 && floorNumber == bottom) {
            status = 1;
        } else if(status == 0) {
            int up = abs(top - floorNumber);
            int down = abs(bottom - floorNumber);
            if(up < down)
                status = 1;
            else status = 2;
        }
    }

}

void Elevator::updateFloor() {
    if(countTarget() == 0)
        return;
    if(status == 1)
        floorNumber++;
    if(status == 2)
        floorNumber--;
}

void Elevator::update() {
    updateStatus();
    if(status == 0)
        return;
    if(clocker == 0) {
        leaveFloor(floorNumber);
        clocker = elevatorSpeed - 1;
    } else if(--clocker == 0) {
        updateFloor(true);
        arriveFloor(floorNumber);
        updateStatus();
    }
}

void Elevator::addTarget( int target ) {
    if(!targetFloor[target] )
        targetFloor[target] = true;
}

bool Elevator::haveTarget(int target) {
//    if(target <= topTarget() && target >= bottomTarget()) {
//        cout << "true" << endl;
//        return true;
//    }
    return target <= topTarget() && target >= bottomTarget();
}

void Elevator::deleteTarget() {
    targetFloor[floorNumber] = false;
}

//void Elevator::setTag( int number ) {
//	tag = number;
//}
//
//int Elevator::getTag() {
//	return tag;
//}

void Elevator::show() {
    // int count = countTarget();
    cout <<
    " floorNumber: " << floorNumber <<
    " status: " << status <<
    " passengerAmount: " << passengerList.size() <<
    " targetAmount: " << countTarget() <<
    " bottomTarget: " << bottomTarget() <<
    " topTarget: " << topTarget() <<
    " clocker: " << clocker <<
    endl;
}