#pragma once

#include "common.h"

class Elevator;

struct Request {
    Floor startingFloor { -1 };
    Floor endingFloor { -1 };
};

constexpr Request noRequest {};

class Passenger {
public:
    Passenger(ID id, Weight weight);

public:
    ID getID() const;
    Weight getWeight() const;
    Floor getCurrentFloor() const;
    Floor getDestinationFloor() const;
    bool hasRequest() const;
    void assignRequest(const Request& request);
    void callElevator(Elevator& elevator) const;
    bool enterElevator(Elevator& elevator);
    bool useElevator();
    void exitElevator();

public:
    friend bool operator== (const Passenger& p1, const Passenger& p2);
    friend bool operator!= (const Passenger& p1, const Passenger& p2);

private:
    const ID id;
    const Weight weight;
    Request request;
    Floor currentFloor;
    Elevator* currentElevator;
};