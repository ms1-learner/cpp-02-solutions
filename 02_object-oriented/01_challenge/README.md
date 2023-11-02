## logger.hpp
```cpp
#pragma once
#include <string>
class Logger {
public:
    void logMessage(const std::string& message);
};
```
## logger.cpp
```cpp
#include "logger.hpp"
#include <iostream>
void Logger::logMessage(const std::string& message) {
    std::cout << message << std::endl;
}
```
## car.cpp (modified)
```cpp
#include "car.hpp"
#include "logger.hpp"
void Car::setPrice(double price) {
    Logger logger;
    logger.logMessage("Changing price from " + std::to_string(this->price) + " to " + std::to_string(price));
    this->price = price;
}
```