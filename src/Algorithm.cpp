#include "Algorithm.hpp"

#include <iostream>
#include <unistd.h>

Algorithm::Algorithm(const Text &pattern, const Text &document)
    : rawPattern_(pattern.getNormalizedContent()), rawDocument_(document.getNormalizedContent())
{}

void Algorithm::run()
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    runWithoutTimeCheck();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    runTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

void Algorithm::runWithoutTimeCheck() { std::cout << "here" << std::endl;}

void Algorithm::printResults()
{
    std::cout << "Time: " << runTime.count() << " us" << std::endl;

    if (occurenceIndexes.empty())
        std::cout << "not matched" << std::endl;

    std::cout << "Pattern occured " << occurenceIndexes.size() << " time(s) at position(s): " << std::endl;
    for (auto it : occurenceIndexes)
        std::cout << "\t" << it << std::endl;
}
