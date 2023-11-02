```cpp

#include <iostream>
#include <vector>
#include <list>

template<typename Container>
void print_elements(const Container& container) {
    for (const auto& element : container) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::list<char> lst = {'a', 'b', 'c', 'd', 'e'};

    print_elements(vec);
    print_elements(lst);

    return 0;
}

```