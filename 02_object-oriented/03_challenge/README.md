## Garage.hpp
```cpp
#pragma once
#include "car.hpp"
#include <vector>
class Garage {
public:
    void addCar(const Car& car);
    void removeCar(int index);
private:
    std::vector<Car> cars;
};
```
## garage.cpp
```cpp
#include "garage.hpp"
void Garage::addCar(const Car& car) {
    cars.push_back(car);
}
void Garage::removeCar(int index) {
    if (index >= 0 && index < cars.size()) {
        cars.erase(cars.begin() + index);
    }
}
```