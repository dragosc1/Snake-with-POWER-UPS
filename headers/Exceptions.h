//
// Created by dragosc1 on 07.05.2023.
//

#ifndef OOP_EXCEPTIONS_H
#define OOP_EXCEPTIONS_H
#include <stdexcept>
#include <string>

class application_error : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class font_error : public application_error {
public:
    explicit font_error() : application_error("Font can't be loaded\n") {}
};

class snake_error : public application_error {
public:
    explicit snake_error() : application_error("Snake got to big\n") {}
};

#endif //OOP_EXCEPTIONS_H
