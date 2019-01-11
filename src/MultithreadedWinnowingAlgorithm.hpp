#ifndef MULTITHREADED_WINNOWING_ALGORITHM_HPP
#define MULTITHREADED_WINNOWING_ALGORITHM_HPP

#include "MultihreadedAlgorithm.hpp"
#include "WinnowingAlgorithm.hpp"

class MultithreadedWinnowingAlgorithm : public MultihreadedAlgorithm, public WinnowingAlgorithm
{
public:
    MultithreadedWinnowingAlgorithm(const Text &pattern, const Text &document, size_t threadsNum);

private:
    void runWithoutTimeCheck() override;
};


#endif /* end of include guard: MULTITHREADED_WINNOWING_ALGORITHM_HPP */
