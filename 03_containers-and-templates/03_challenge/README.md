```cpp

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <chrono>

constexpr int NUM_OPERATIONS = 100000;

template <typename T, typename Container>
class Stack {
public:
    void push(const T& value) {
        data.push_back(value);
    }

    void pop() {
        if (!is_empty()) {
            data.pop_back();
        }
    }

    T& top() {
        return data.back();
    }

    bool is_empty() const {
        return data.empty();
    }

private:
    Container data;
};

template<typename StackType>
void measure_performance() {
    StackType stack;
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        stack.push(i);
    }

    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        stack.pop();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    
    std::cout << "Time taken: " << duration << " microseconds" << std::endl;
}

int main() {
    std::cout << "Using std::vector:" << std::endl;
    measure_performance<Stack<int, std::vector<int>>>();

    std::cout << "Using std::list:" << std::endl;
    measure_performance<Stack<int, std::list<int>>>();

    std::cout << "Using std::deque:" << std::endl;
    measure_performance<Stack<int, std::deque<int>>>();

    return 0;
}

```