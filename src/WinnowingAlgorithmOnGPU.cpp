#include "WinnowingAlgorithmOnGPU.hpp"

#include <functional>

WinnowingAlgorithmOnGPU::WinnowingAlgorithmOnGPU(const Text &pattern, const Text &document)
    : AlgorithmOnGPU(pattern, document)
{
    kernelFile_ = "../res/kernels/winnowing.cl";
    kernelProgramName_ = "winnowing";
}

void WinnowingAlgorithmOnGPU::preRun()
{
    documentBuffer_ = cl::Buffer{context_, CL_MEM_READ_WRITE, sizeof(char) * rawDocument_.size()};
    resultBuffer_ = cl::Buffer{context_, CL_MEM_READ_WRITE, sizeof(char) * lastPossibleIndex_};

    queue_.enqueueWriteBuffer(documentBuffer_, CL_TRUE, 0, sizeof(char) * rawDocument_.size(), rawDocument_.data());
    queue_.enqueueWriteBuffer(resultBuffer_, CL_TRUE, 0, sizeof(char)*lastPossibleIndex_, occurenceIndexes_.data());
    auto kernelCode = readKernelCode(kernelFile_);
    cl::Program::Sources sources = {{kernelCode.c_str(), kernelCode.length()}};

    program_ = cl::Program{context_, sources};
    if (program_.build({defaultDevice_}) != CL_SUCCESS) {
        std::string msg = "OpenCL: program build failed";
        auto buildLog = program_.getBuildInfo<CL_PROGRAM_BUILD_LOG>(defaultDevice_);
        throw std::runtime_error{msg + "\n" + buildLog};
    }

    kernel_ = cl::Kernel{program_, kernelProgramName_.c_str()};
    cl_ulong patternLen = rawPattern_.size();
    auto patternHash = hash(rawPattern_);
    kernel_.setArg(0, documentBuffer_);
    kernel_.setArg(1, patternHash);
    kernel_.setArg(2, patternLen);
    kernel_.setArg(3, resultBuffer_);

    queue_.enqueueNDRangeKernel(kernel_, cl::NullRange, cl::NDRange(lastPossibleIndex_), cl::NullRange);
}

void WinnowingAlgorithmOnGPU::postRun()
{
    queue_.enqueueReadBuffer(resultBuffer_, CL_TRUE, 0, sizeof(char)*lastPossibleIndex_, occurenceIndexes_.data());
}

cl_ulong WinnowingAlgorithmOnGPU::hash(const std::string& str) const
{
    cl_ulong res = 0;

    for (const auto it : str) {
        res += it;
        res += res << 10;
        res ^= res >> 6;
    }

    res += res << 3;
    res ^= res >> 11;
    res += res << 15;
    return res;
}
