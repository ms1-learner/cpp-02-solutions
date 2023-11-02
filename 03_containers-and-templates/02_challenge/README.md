```cpp

#include <iostream>
#include <vector>
#include <list>

template<typename T, typename Container = std::vector<T>>
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

    T top() const {
        if (!is_empty()) {
            return data.back();
        } else {
            throw std::runtime_error("Stack is empty");
        }
    }

    bool is_empty() const {
        return data.empty();
    }

private:
    Container data;
};

int main() {
    Stack<int> int_vector_stack;
    int_vector_stack.push(1);
    int_vector_stack.push(2);
    std::cout << int_vector_stack.top() << std::endl; // Output: 2
    int_vector_stack.pop();
    std::cout << int_vector_stack.top() << std::endl; // Output: 1
    
    Stack<char, std::list<char>> char_list_stack;
    char_list_stack.push('a');
    char_list_stack.push('b');
    std::cout << char_list_stack.top() << std::endl; // Output: b
    char_list_stack.pop();
    std::cout << char_list_stack.top() << std::endl; // Output: a

    return 0;
}

```