#ifndef NAIVE_ALGORITHM_ON_GPU_HPP
#define NAIVE_ALGORITHM_ON_GPU_HPP

#include "AlgorithmOnGPU.hpp"

class NaiveAlgorithmOnGPU : public AlgorithmOnGPU
{
public:
    NaiveAlgorithmOnGPU(const Text &pattern, const Text &document);
    virtual ~NaiveAlgorithmOnGPU() = default;
};

#endif /* end of include guard: NAIVE_ALGORITHM_ON_GPU_HPP */
