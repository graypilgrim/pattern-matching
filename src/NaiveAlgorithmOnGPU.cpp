#include "NaiveAlgorithmOnGPU.hpp"

#include <sstream>

NaiveAlgorithmOnGPU::NaiveAlgorithmOnGPU(const Text &pattern, const Text &document)
    : AlgorithmOnGPU(pattern, document)
{
    kernelFile_ = "../res/kernels/naive.cl";
    kernelProgramName_ = "naive";
}

void NaiveAlgorithmOnGPU::preRun()
{
    documentBuffer_ = cl::Buffer{context_, CL_MEM_READ_WRITE, sizeof(char) * rawDocument_.size()};
    patternBuffer_ = cl::Buffer{context_, CL_MEM_READ_WRITE, sizeof(char) * rawPattern_.size()};
    resultBuffer_ = cl::Buffer{context_, CL_MEM_READ_WRITE, sizeof(char) * lastPossibleIndex_};

    queue_.enqueueWriteBuffer(documentBuffer_, CL_TRUE, 0, sizeof(char) * rawDocument_.size(), rawDocument_.data());
    queue_.enqueueWriteBuffer(patternBuffer_, CL_TRUE, 0, sizeof(char) * rawPattern_.size(), rawPattern_.data());
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
    kernel_.setArg(0, documentBuffer_);
    kernel_.setArg(1, patternBuffer_);
    kernel_.setArg(2, patternLen);
    kernel_.setArg(3, resultBuffer_);

    queue_.enqueueNDRangeKernel(kernel_, cl::NullRange, cl::NDRange(lastPossibleIndex_), cl::NullRange);
}

void NaiveAlgorithmOnGPU::postRun()
{
    queue_.enqueueReadBuffer(resultBuffer_, CL_TRUE, 0, sizeof(char)*lastPossibleIndex_, occurenceIndexes_.data());
}
