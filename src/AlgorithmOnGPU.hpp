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
    std::string readKernelCode(const std::string& fileName) const;

    cl::Context context_;
    cl::Program program_;
    cl::CommandQueue queue_;
    cl::Kernel kernel_;
    cl::Device defaultDevice_;
    std::string kernelProgramName_;
    std::string kernelFile_;

    void runWithoutTimeCheck() override;

private:
};

#endif /* end of include guard: ALGORITHM_ON_GPU_HPP */
