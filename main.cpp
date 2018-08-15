#include "Building.h"
#include "Floor.h"
#include "Elevator.h"
#include "Passenger.h"

int main() {
    cout << "----程序开始----" << endl;
    srand(time(0));
    Building building;
    cout << "输入数字分别代表楼层数，电梯数和乘客数量：";
    int floorAmount, elevatorAmount, passengerAmount;
    while(1) {
        cin >> floorAmount >> elevatorAmount >> passengerAmount;
        if(floorAmount <= 0 || elevatorAmount <= 0 || passengerAmount <= 0)
            cout << "嘤嘤嘤！重新输:";
        else break;
    }
    for(int i = 0; i < floorAmount; i++) {
        new Floor(i, &building);
    }
    for(int i = 0; i < elevatorAmount; i++) {
        Elevator *elevator = new Elevator(&building);
    }

    for(int i = 0; i < passengerAmount; i++) {
        new Passenger(&building);
    }
    cin.get();
    cout << "----初始化结束----" << endl;
    int times = 0;
    while(true) {
        cout << "输入运行次数(负数退出）：";
        cin >> times;
        building.run(times);
        if(times < 0)
            break;
//        if(times < -1)
//            break;
//        else if(times == -1)
//            building.show();
//        else
//            building.run(times);
    }
    cout << "----运行结束----" << endl;
    return 0;
}