## driver.hpp
```cpp
#pragma once
#include <string>
class Driver {
public:
    Driver(const std::string& name, int age);
private:
    std::string name;
    int age;
};
```
## driver.cpp
```cpp
#include "driver.hpp"
Driver::Driver(const std::string& name, int age)
    : name(name), age(age) {}
```
## car.hpp (modified)
```cpp
class Car {
public:
    // ...
    void setDriver(Driver* driver);
private:
    // ...
    Driver* driver;
};
```
## car.cpp (modified)
```cpp
#include "car.hpp"
#include "driver.hpp"
void Car::setDriver(Driver* driver) {
    this->driver = driver;
}
```