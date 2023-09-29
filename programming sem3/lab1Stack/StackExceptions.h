//
// Created by Антон on 05.09.2023.
//

#ifndef LAB1STACK_STACKEXCEPTIONS_H
#define LAB1STACK_STACKEXCEPTIONS_H

#include <exception>

namespace stackLab{

class badStackSize: public std::exception{
public:
    [[nodiscard]] const char* what() const noexcept override{
        return exception::what();
    }
};

class popOutOfRange: public std::exception{
    [[nodiscard]] const char* what() const noexcept override{
        return exception::what();
    }
};
}

#endif //LAB1STACK_STACKEXCEPTIONS_H
