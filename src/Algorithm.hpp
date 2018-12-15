#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <vector>
#include <chrono>

#include "Text.hpp"

class Algorithm
{
public:
    Algorithm(const Text &pattern, const Text &document);
    void run();
    void printResults();

protected:
    std::string rawPattern_;
    std::string rawDocument_;
    std::vector<size_t> occurenceIndexes;
    std::chrono::microseconds runTime;

private:
    virtual void runWithoutTimeCheck() = 0;
    //TODO: template with class name
};


#endif /* end of include guard: ALGORITHM_HPP */
