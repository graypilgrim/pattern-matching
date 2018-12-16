#ifndef PARALLEL_WINNOWING_ALGORITHM_HPP
#define PARALLEL_WINNOWING_ALGORITHM_HPP

#include "ParallelAlgorithm.hpp"
#include "WinnowingAlgorithm.hpp"

class ParallelWinnowingAlgorithm : public ParallelAlgorithm, public WinnowingAlgorithm
{
public:
    ParallelWinnowingAlgorithm(const Text &pattern, const Text &document, size_t threadsNum);

private:
    void runWithoutTimeCheck() override;
};


#endif /* end of include guard: PARALLEL_WINNOWING_ALGORITHM_HPP */
