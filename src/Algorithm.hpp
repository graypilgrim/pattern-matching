#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "Text.hpp"

class Algorithm
{
public:
    Algorithm(const Text &pattern, const Text &document);
    void run();
    void printResults();

private:
    virtual void runWithoutTimeCheck() = 0;
    //TODO: template with class name
};


#endif /* end of include guard: ALGORITHM_HPP */
