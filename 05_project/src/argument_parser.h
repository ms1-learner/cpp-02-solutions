#pragma once

#include <sstream>
#include <string>
#include <iostream>

class ArgumentParser {
public:
    ArgumentParser(int argc, char **argv, const std::string& usageMessage)
        : argc(argc), argv(argv), usageMessage(usageMessage), index(1) {}

public:
    template <typename T>
    T get() {
        if (argc <= index) {
            throw std::runtime_error(usageMessage);
        }

        return extractArg<T>();
    }

    template <typename T>
    T getOptional(const T& defaultValue) {
        if (argc <= index) {
            return defaultValue;
        }

        return extractArg<T>();
    }

private:
    template <typename T>
    T extractArg() {
        T arg {};
        std::istringstream iss { argv[index] };
        if(!(iss >> arg)) {
            throw std::runtime_error(usageMessage);
        }
        ++index;
        return arg;
    }

private:
    int argc;
    char **argv;
    std::string usageMessage;
    int index;
};