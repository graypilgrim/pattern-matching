#include "NaiveAlgorithmOnGPU.hpp"

#include <sstream>

NaiveAlgorithmOnGPU::NaiveAlgorithmOnGPU(const Text &pattern, const Text &document)
    : AlgorithmOnGPU(pattern, document)
{
    auto size = sizeof(char) * rawPattern_.size();
    documentBuffer_ = cl::Buffer{context_, CL_MEM_READ_WRITE, size};
    patternBuffer_ = cl::Buffer{context_, CL_MEM_READ_WRITE, size};
    resultBuffer_ = cl::Buffer{context_, CL_MEM_READ_WRITE, sizeof(unsigned char)};
}

void NaiveAlgorithmOnGPU::runWithoutTimeCheck()
{
    const size_t resultArrayLen = 1;
    char resultArray[resultArrayLen] = {COMPARISON_MARKER};
    const auto patternSize = sizeof(char) * rawPattern_.size();
    const auto resultArraySize = sizeof(char);

    cl::Kernel kernel{program_,"compare"};

    for (auto i = 0u; i < lastPossibleIndex_; ++i) {
        resultArray[0] = COMPARISON_MARKER;
        queue_.enqueueWriteBuffer(patternBuffer_, CL_TRUE, 0, patternSize, rawPattern_.data());
        queue_.enqueueWriteBuffer(resultBuffer_, CL_TRUE, 0, resultArraySize, resultArray);
        queue_.enqueueWriteBuffer(documentBuffer_, CL_TRUE, 0, patternSize, rawDocument_.data() + i);

        kernel.setArg(0, documentBuffer_);
        kernel.setArg(1, patternBuffer_);
        kernel.setArg(2, resultBuffer_);
        queue_.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(rawPattern_.size()), cl::NullRange);
        queue_.finish();

        queue_.enqueueReadBuffer(resultBuffer_, CL_TRUE, 0, sizeof(unsigned char), resultArray);

        if (resultArray[0] == COMPARISON_MARKER) occurenceIndexes_[i] = 1;
    }
}
