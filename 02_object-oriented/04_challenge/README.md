## car.cpp (modified)
```cpp
#include "car.hpp"
#include "tire.hpp"
Car::Car(std::string make, std::string model, int year, double price)
    : make(make), model(model), year(year), price(price), tire(17, "All-season") {}
```
## tire.hpp
```cpp
#pragma once
#include <string>
class Tire {
public:
    Tire(int size, const std::string& type);
    int size;
    std::string type;
};
```
## tire.cpp
```cpp
#include "tire.hpp"
Tire::Tire(int size, const std::string& type)
    : size(size), type(type) {}
```