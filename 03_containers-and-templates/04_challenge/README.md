```cpp

#include <iostream>
#include <string>
#include <map>
#include <fstream>

class PhoneBook {
public:
    void add_entry(const std::string& name, const std::string& number) {
        phone_book[name] = number;
    }

    void remove_entry(const std::string& name) {
        phone_book.erase(name);
    }

    std::string find_number(const std::string& name) const {
        auto it = phone_book.find(name);
        if (it != phone_book.end()) {
            return it->second;
        } else {
            return "Name not found";
        }
    }

    void display() const {
        for (const auto& entry : phone_book) {
            std::cout << entry.first << ": " << entry.second << std::endl;
        }
    }

    void load_from_file(const std::string& file_path) {
        std::ifstream input_file(file_path);

        if (!input_file) {
            std::cerr << "Error opening input file" << std::endl;
            return;
        }

        std::string name, number;
        while (input_file >> name >> number) {
            add_entry(name, number);
        }

        input_file.close();
    }

private:
    std::map<std::string, std::string> phone_book;
};

int main() {
    PhoneBook phone_book;
    phone_book.load_from_file("phone_numbers.txt");

    phone_book.display();

    std::cout << std::endl << "Adding a new entry (John, 555-1234):" << std::endl;
    phone_book.add_entry("John", "555-1234");
    phone_book.display();

    std::cout << std::endl << "Removing an entry (John):" << std::endl;
    phone_book.remove_entry("John");
    phone_book.display();

    std::cout << std::endl << "Searching for a number by name (Alice): ";
    std::string number = phone_book.find_number("Alice");
    std::cout << number << std::endl;

    return 0;
}

```