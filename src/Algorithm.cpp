#include "Algorithm.hpp"

/*
 * below constructor is not called anywhere explicitly but lack of it
 * caused build error on gcc 6
*/
Algorithm::Algorithm()
    :lastPossibleIndex_(0)
{}

Algorithm::Algorithm(const Text &pattern, const Text &document)
    : rawPattern_(pattern.getNormalizedContent()),
      rawDocument_(document.getNormalizedContent()),
      lastPossibleIndex_(rawDocument_.size() - rawPattern_.size()),
      occurenceIndexes_(lastPossibleIndex_, 0)
{}

void Algorithm::run()
{
    preRun();
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    runWithoutTimeCheck();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    runTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    postRun();
}

void Algorithm::printResults()
{
    std::cout << "Time: " << runTime.count() << " us" << std::endl;

    if (occurenceIndexes_.empty())
        std::cout << "not matched" << std::endl;

    size_t sum = 0;
    std::cout << "Pattern occured at position(s): " << std::endl;
    for (auto i = 0u; i < lastPossibleIndex_; ++i) {
        if (occurenceIndexes_[i]) {
            std::cout << "\t" << i << std::endl;
            ++sum;
        }
    }
    std::cout << "Total: " << sum <<  std::endl;
}
