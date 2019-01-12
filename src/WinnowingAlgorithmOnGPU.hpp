#ifndef WINNOWING_ALGORITHM_ON_GPU_HPP
#define WINNOWING_ALGORITHM_ON_GPU_HPP

#include "AlgorithmOnGPU.hpp"

#include <string>

class WinnowingAlgorithmOnGPU : public AlgorithmOnGPU
{
public:
    WinnowingAlgorithmOnGPU(const Text &pattern, const Text &document);
    virtual ~WinnowingAlgorithmOnGPU() = default;

private:
    void preRun() override;
    void postRun() override;
    cl_ulong hash(const std::string& str) const;

    cl::Buffer documentBuffer_;
    cl::Buffer resultBuffer_;
};

#endif /* end of include guard: WINNOWING_ALGORITHM_ON_GPU_HPP */
