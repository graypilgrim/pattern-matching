#ifndef PARALLEL_ALGORITHM_HPP
#define PARALLEL_ALGORITHM_HPP

#include "Algorithm.hpp"

#include <omp.h>

class ParallelAlgorithm : public virtual Algorithm
{
public:
    ParallelAlgorithm(const Text &pattern, const Text &document, size_t threadsNum);
    virtual ~ParallelAlgorithm() = default;

protected:
    const size_t threadsNum_ = 4;
};

#endif /* end of include guard: PARALLEL_ALGORITHM_HPP */
