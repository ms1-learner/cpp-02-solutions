```cpp

#include <iostream>
#include <string>

enum class TrafficLight {
    red,
    yellow,
    green
};

std::string get_action(TrafficLight light) {
    switch (light) {
        case TrafficLight::Red: return "Stop";
        case TrafficLight::Yellow: return "Caution";
        case TrafficLight::Green: return "Go";
        default: return "Invalid traffic light color";
    }
}

int main() {
    TrafficLight light = TrafficLight::Red;
    std::cout << get_action(light) << std::endl;
    return 0;
}

```