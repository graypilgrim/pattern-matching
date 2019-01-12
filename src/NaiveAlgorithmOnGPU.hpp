#ifndef NAIVE_ALGORITHM_ON_GPU_HPP
#define NAIVE_ALGORITHM_ON_GPU_HPP

#include "AlgorithmOnGPU.hpp"

class NaiveAlgorithmOnGPU : public AlgorithmOnGPU
{
public:
    NaiveAlgorithmOnGPU(const Text &pattern, const Text &document);
    virtual ~NaiveAlgorithmOnGPU() = default;

private:
    cl::Buffer documentBuffer_;
    cl::Buffer patternBuffer_;
    cl::Buffer resultBuffer_;

    void preRun() override;
    void postRun() override;
};

#endif /* end of include guard: NAIVE_ALGORITHM_ON_GPU_HPP */
