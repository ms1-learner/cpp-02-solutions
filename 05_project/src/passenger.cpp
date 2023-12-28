#include "passenger.h"
#include "elevator.h"
#include <iostream>

Passenger::Passenger(ID id, Weight weight) : id(id), weight(weight), currentFloor(groundFloor), currentElevator(nullptr) {
    if (weight < 0) {
        throw std::runtime_error("Exception! Invalid passenger weight");
    }
}

ID Passenger::getID() const {
    return id;
}

Weight Passenger::getWeight() const {
    return weight;
}

Floor Passenger::getCurrentFloor() const {
    if (currentElevator != nullptr) {
        return currentElevator->getCurrentFloor();
    } else {
        return currentFloor;
    }
}

Floor Passenger::getDestinationFloor() const {
    return request.endingFloor;
}

bool Passenger::hasRequest() const {
    return request.startingFloor != -1 && request.endingFloor != -1;
}

void Passenger::assignRequest(const Request& request) {
    if (request.startingFloor != currentFloor) {
        throw std::runtime_error("Exception! Passenger cannot request an elevator from a different floor than its current floor.");
    }
    if (request.endingFloor < 0) {
        throw std::runtime_error("Exception! Passenger cannot request an invalid destination floor.");
    }
    this->request = request;
}

void Passenger::callElevator(Elevator& elevator) const {
    elevator.callFromFloor(currentFloor);
    std::cout << "Passenger " << id << " called elevator to floor " << currentFloor << std::endl;
}

bool Passenger::enterElevator(Elevator& elevator) {
    std::cout << "Passenger " << id << " tried to enter the elevator" << std::endl;
    bool couldEnter { elevator.enter(*this) };
    if (couldEnter) {
        currentElevator = &elevator;
        currentFloor = inElevator;
        std::cout << "Passenger " << id << " entered elevator" << std::endl;
    } else {
        std::cout << "Passenger " << id << " could not stay in the elevator" << std::endl;
    }
    return couldEnter;
}

bool Passenger::useElevator() {
    if (currentElevator == nullptr) {
        throw std::runtime_error("Exception! Passenger cannot use an elevator if it isn't already in one");
    }

    bool couldUse { currentElevator->requestDestinationFloor(request.endingFloor) };
    if (couldUse) {
        std::cout << "Passenger " << id << " requested floor " << request.endingFloor << std::endl;
    }
    return couldUse;
}

void Passenger::exitElevator() {
    if (currentElevator == nullptr) {
        throw std::runtime_error("Exception! Passenger cannot exit an elevator if it isn't already in one");
    }

    currentElevator->leave(*this);
    currentFloor = currentElevator->getCurrentFloor();
    currentElevator = nullptr;
    request = noRequest;
    std::cout << "Passenger " << id << " left elevator on floor " << currentFloor << std::endl;
}

bool operator== (const Passenger& p1, const Passenger& p2) {
    return p1.id == p2.id;
}

bool operator!= (const Passenger& p1, const Passenger& p2) {
    return !(p1 == p2);
}