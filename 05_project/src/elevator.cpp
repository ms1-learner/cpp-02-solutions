#include "elevator.h"
#include "passenger.h"
#include <iostream>
#include <cmath>

Elevator::Elevator(Floor floors, Weight weightCapacity) : floors(floors), weightCapacity(weightCapacity), currentFloor(groundFloor), destinationFloor(noDestination), elapsedTime(0) {
    if (floors < 1) {
        throw std::runtime_error("Exception! Invalid number of floors.");
    }
    if (weightCapacity < 0) {
        throw std::runtime_error("Exception! Invalid weight capacity.");
    }
}

Floor Elevator::getFloors() {
    return floors;
}

Floor Elevator::getCurrentFloor() const {
    return currentFloor;
}

Time Elevator::getElapsedTime() const {
    return elapsedTime;
}

void Elevator::callFromFloor(Floor floor) {
    bool notRequested { true };
    for (auto pickUpRequest : pickUpRequests) {
        if (pickUpRequest == floor) {
            notRequested = false;
            break;
        }
    }

    if (notRequested) {
        pickUpRequests.push_back(floor);
    }
}

bool Elevator::enter(const Passenger& passenger) {
    if (passenger.getCurrentFloor() != getCurrentFloor()) {
        throw std::runtime_error("Exception! Passenger can only enter if the elevator is on the same floor!");
    }

    Weight currentWeight { 0 };
    for (auto existingPassenger : passengers) {
        if (passenger == *existingPassenger) {
            throw std::runtime_error("Exception! We shouldn't be picking up a passenger that is already in the elevator!");
        }
        currentWeight += existingPassenger->getWeight();
    }

    if (currentWeight + passenger.getWeight() > weightCapacity) {
        return false;
    }

    passengers.push_back(&passenger);
    
    return true;
}

bool Elevator::requestDestinationFloor(Floor floor) {
    bool notRequested { true };
    for (auto dropOffRequest : dropOffRequests) {
        if (dropOffRequest == floor) {
            notRequested = false;
            break;
        }
    }

    if (notRequested) {
        dropOffRequests.push_back(floor);
    }

    return true; 
}

void Elevator::leave(const Passenger& passenger) {
    for (auto it { passengers.begin() }; it != passengers.end(); ++it) {
        if (passenger == **it) {
            passengers.erase(it);
            return;
        }
    }

    throw std::runtime_error("Exception! We shouldn't be dropping off a passenger that isn't already in the elevator!");
}

void Elevator::run() {
    if (destinationFloor == noDestination) {
        goToDestination(pickUpRequests);
    } else {
        goToDestination(dropOffRequests);
        if (dropOffRequests.empty()) {
            destinationFloor = noDestination;
        }
    }
}

void Elevator::goToDestination(std::vector<Floor>& requests) {
    if (requests.empty()) {
        return;
    }

    destinationFloor = requests.front();
    Floor floorDifference { destinationFloor - currentFloor };
    if (floorDifference > 0) {
        ++currentFloor;
        ++elapsedTime;
    } else if (floorDifference < 0) {
        --currentFloor;
        ++elapsedTime;
    }

    std::cout << "Elevator arrived at floor " << currentFloor << std::endl;

    if (destinationFloor == currentFloor) {
        requests.erase(requests.begin());
    }
}

/*
基本:
エレベーター1台

はじめに次の値を記載したinput.txtを使用する:

30 500
0 64 0 10

ヒント:
- ヘッダーファイルでインターフェイスを設計するところから始めます。同時に、そのインターフェイスで機能を実装するためには、各クラスにどのようなプライベート(private)メンバが必要かを考えます。
- インターフェイスが決まったら、ソースファイルでロジックを実装します。

*/