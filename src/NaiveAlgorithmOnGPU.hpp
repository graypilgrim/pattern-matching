#ifndef NAIVE_ALGORITHM_ON_GPU_HPP
#define NAIVE_ALGORITHM_ON_GPU_HPP

#include "AlgorithmOnGPU.hpp"

class NaiveAlgorithmOnGPU : public AlgorithmOnGPU
{
public:
    NaiveAlgorithmOnGPU(const Text &pattern, const Text &document);
    virtual ~NaiveAlgorithmOnGPU() = default;

private:
    void runWithoutTimeCheck() override;

    cl::Buffer documentBuffer_;
    cl::Buffer patternBuffer_;
    cl::Buffer resultBuffer_;

    static const char COMPARISON_MARKER = 23;
    const std::string KERNEL_PROGRAM_NAME = "compare";
};

#endif /* end of include guard: NAIVE_ALGORITHM_ON_GPU_HPP */
