#pragma once

#include "common.h"
#include <vector>

class Passenger;

class Elevator {
public:
    Elevator(Floor floors, Weight weightCapacity);

public:
    Floor getFloors();
    Floor getCurrentFloor() const;
    Time getElapsedTime() const;
    void callFromFloor(Floor floor);            // 乗客からの呼び出し
    bool enter(const Passenger& passenger);     // 乗客からの呼び出し
    bool requestDestinationFloor(Floor floor);  // 乗客からの呼び出し
    void leave(const Passenger& passenger);     // 乗客からの呼び出し
    void run();

private:
    void goToDestination(std::vector<Floor>& requests);

private:
    const Floor floors;
    const Weight weightCapacity;
    Floor currentFloor;
    Floor destinationFloor;
    Time elapsedTime;
    std::vector<const Passenger*> passengers;
    std::vector<Floor> pickUpRequests;
    std::vector<Floor> dropOffRequests;
};