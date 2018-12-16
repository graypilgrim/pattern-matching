#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <vector>
#include <chrono>
#include <iostream>

#include "Text.hpp"

class Algorithm
{
public:
    Algorithm(const Text &pattern, const Text &document);
    virtual ~Algorithm() = default;
    void run();
    void printResults();

protected:
    std::string rawPattern_;
    std::string rawDocument_;
    std::vector<size_t> occurenceIndexes;
    std::chrono::microseconds runTime;

private:
    virtual void runWithoutTimeCheck() = 0;
};


#endif /* end of include guard: ALGORITHM_HPP */
