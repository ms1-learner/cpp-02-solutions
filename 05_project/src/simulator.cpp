#include "simulator.h"
#include "elevator.h"
#include "passenger.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <thread>
#include <chrono>

std::ifstream openFile(const std::string& filename);

Simulator::Simulator(int millisecondsDelay) : millisecondsDelay(millisecondsDelay) {}

void Simulator::initializeFromFile(const std::string& filename) {
    auto file { openFile(filename) };
    parseElevators(file);
    parsePassengers(file);
    parseInputs(file);
    elapsedTime = 0;
}

std::ifstream openFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Exception! Cannot open file!");
    }

    return file;
}

void Simulator::parseElevators(std::ifstream& file) {
    std::string line;
    std::getline(file, line);
    std::istringstream iss { line };

    int numberOfElevators { -1 };
    Floor numberOfFloors { -1 };
    Weight elevatorCapacity { -1 };
    if (!(iss >> numberOfElevators >> numberOfFloors >> elevatorCapacity)) {
        throw std::runtime_error("Exception! Cannot parse the first line of the file!");
    }

    if (numberOfElevators < 1) {
        throw std::runtime_error("Exception! Invalid number of elevators!");
    }

    this->numberOfFloors = numberOfFloors;
    this->elevators = std::vector<Elevator>(numberOfElevators, { numberOfFloors, elevatorCapacity });
}

void Simulator::parsePassengers(std::ifstream& file) {
    std::string line;
    std::getline(file, line);
    std::istringstream iss { line };

    int numberOfPassengers {};
    if (!(iss >> numberOfPassengers)) {
        throw std::runtime_error("Exception! Cannot parse the number of passengers!");
    }

    this->statefulPassengers.clear();

    while (numberOfPassengers-- && std::getline(file, line)) {
        iss = std::istringstream { line };

        ID id;
        Weight weight;

        if (!(iss >> id >> weight)) {
            throw std::runtime_error("Exception! Cannot parse the remaining lines of the file!");
        }

        if (weight < 0) {
            throw std::runtime_error("Exception! Invalid weight!");
        }

        this->statefulPassengers.emplace_back(Passenger{id, weight});
    }
}

void Simulator::parseInputs(std::ifstream& file) {
    std::string line;
    while (std::getline(file, line)) {
        auto iss = std::istringstream { line };

        Input input {};

        if (!(iss >> input.time >> input.id >> input.pickUpFloor >> input.dropOffFloor)) {
            throw std::runtime_error("Exception! Cannot parse the remaining lines of the file!");
        }

        if (input.time < 0) {
            throw std::runtime_error("Exception! Invalid time!");
        }

        if (input.pickUpFloor < 0 || input.pickUpFloor > numberOfFloors) {
            throw std::runtime_error("Exception! Invalid pick-up floor!");
        }

        if (input.dropOffFloor < 0 || input.dropOffFloor > numberOfFloors) {
            throw std::runtime_error("Exception! Invalid drop-off floor!");
        }

        this->inputs.push_back(input);
    }
}

void Simulator::run() {
    while(canRun()) {
        handleInputs();
        handlePassengers();
        handleElevators();
        handleTime();
    }
}

bool Simulator::canRun() const {
    bool anyPassengersAreActive { false };
    for (const auto& statefulPassenger : statefulPassengers) {
        if (statefulPassenger.state != StatefulPassenger::state::idle) {
            anyPassengersAreActive = true;
            break;
        }
    }

    bool anyInputsAreActive { false };
    for (const auto& input : inputs) {
        if (input.time != -1) {
            anyInputsAreActive = true;
            break;
        }
    }

    return anyPassengersAreActive || anyInputsAreActive;
}

void Simulator::handleInputs() {
    for (auto& input : inputs) {
        if (input.time != elapsedTime) {
            continue;
        }

        for (auto& statefulPassenger : statefulPassengers) {
            auto& passenger { statefulPassenger.passenger };
            if (passenger.getID() == input.id) {
                passenger.assignRequest({input.pickUpFloor, input.dropOffFloor});
                input = noInput;
            }
        }
    }
}

void Simulator::handlePassengers() {
    for (auto& statefulPassenger : statefulPassengers) {
        auto& state { statefulPassenger.state };
        auto& passenger { statefulPassenger.passenger };

        switch (state) {
            case StatefulPassenger::state::idle : {
                if (passenger.hasRequest()) {
                    passenger.callElevator(elevators.front());
                    state = StatefulPassenger::state::waiting;
                }
                break;
            }
            case StatefulPassenger::state::waiting : {
                if (elevatorArrivedToFloor(passenger.getCurrentFloor())) {
                    if (passenger.enterElevator(elevators.front())) {
                        if (passenger.useElevator()) {
                            state = StatefulPassenger::state::riding;
                        } else {
                            passenger.exitElevator();
                            state = StatefulPassenger::state::idle;
                        }
                    } else {
                        state = StatefulPassenger::state::idle;
                    }
                }
                break;
            }
            case StatefulPassenger::state::riding : {
                if (elevatorArrivedToFloor(passenger.getDestinationFloor())) {
                    passenger.exitElevator();
                    state = StatefulPassenger::state::idle;
                }
                break;
            }
        }
    }
}

bool Simulator::elevatorArrivedToFloor(Floor floor) const {
    for (const auto& elevator : elevators) {
        if (elevator.getCurrentFloor() == floor) {
            return true;
        }
    }
    return false;
}

void Simulator::handleElevators() {
    for (auto& elevator : elevators) {
        elevator.run();
    }
}

void Simulator::handleTime() {
    ++elapsedTime;
    std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsDelay));
}

void Simulator::printResults() const {
    std::cout << std::endl << "Total elapsed time: " << elapsedTime << std::endl << std::endl;
}