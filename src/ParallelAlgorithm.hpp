#ifndef PARALLEL_ALGORITHM_HPP
#define PARALLEL_ALGORITHM_HPP

#include "Algorithm.hpp"

class ParallelAlgorithm : public Algorithm
{
public:
    ParallelAlgorithm(const Text &pattern, const Text &document, size_t threadsNum);

protected:
    const size_t threadsNum_ = 4;
};

#endif /* end of include guard: PARALLEL_ALGORITHM_HPP */
