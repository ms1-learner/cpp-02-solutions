```cpp

#include <iostream>

struct Rectangle {
    float width;
    float height;
};

constexpr double rectangle_area(const Rectangle& rect) {
    return rect.width * rect.height;
}

int main() {
    Rectangle rect{3.0f, 4.0f};
    std::cout << "Area: " << rectangle_area(rect) << std::endl;
    return 0;
}

```