#ifndef MULTITHREADED_ALGORITHM_HPP
#define MULTITHREADED_ALGORITHM_HPP

#include "Algorithm.hpp"

#include <omp.h>

class MultihreadedAlgorithm : public virtual Algorithm
{
public:
    MultihreadedAlgorithm(const Text &pattern, const Text &document, size_t threadsNum);
    virtual ~MultihreadedAlgorithm() = default;

protected:
    const size_t threadsNum_ = 4;
};

#endif /* end of include guard: MULTITHREADED_ALGORITHM_HPP */
