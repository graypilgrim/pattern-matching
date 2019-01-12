#ifndef ALGORITHM_ON_GPU_HPP
#define ALGORITHM_ON_GPU_HPP

#include "Algorithm.hpp"

#include <CL/cl.hpp>

#include <iostream>

class AlgorithmOnGPU : public Algorithm
{
public:
    AlgorithmOnGPU(const Text &pattern, const Text &document);

protected:
    cl::Context context_;
    cl::Program program_;
    cl::CommandQueue queue_;
    cl::Buffer documentBuffer_;
    cl::Buffer patternBuffer_;
    cl::Buffer resultBuffer_;
    cl::Kernel kernel_;
    std::string readKernelCode(const std::string& fileName) const;
    const std::string KERNEL_FILE = "../res/kernels/kernel_compare.cl";
    std::string KERNEL_PROGRAM_NAME = "";

    void runWithoutTimeCheck() override;

private:
};

#endif /* end of include guard: ALGORITHM_ON_GPU_HPP */
