#pragma once

#include "common.h"
#include "passenger.h"
#include "elevator.h"
#include <string>
#include <vector>

namespace {
struct StatefulPassenger {
    enum class state { idle, waiting, riding };

    StatefulPassenger(const Passenger& passenger) : passenger(passenger) {}

    state state { state::idle };
    Passenger passenger;
};

struct Input {
    Time time { -1 };
    ID id { -1 };
    Floor pickUpFloor { -1 };
    Floor dropOffFloor { -1 };
};

constexpr Input noInput {};
}

class Simulator {
public:
    Simulator(int millisecondsDelay);

public:
    void initializeFromFile(const std::string& filename);
    void run();
    void printResults() const;

private:
    bool canRun() const;
    void parseElevators(std::ifstream& file);
    void parsePassengers(std::ifstream& file);
    void parseInputs(std::ifstream& file);
    void handleInputs();
    void handlePassengers();
    bool elevatorArrivedToFloor(Floor floor) const;
    void handleElevators();
    void handleTime();

private:
    const int millisecondsDelay;
    Time elapsedTime { 0 };
    Floor numberOfFloors { -1 };
    std::vector<Elevator> elevators;
    std::vector<StatefulPassenger> statefulPassengers;
    std::vector<Input> inputs;
};