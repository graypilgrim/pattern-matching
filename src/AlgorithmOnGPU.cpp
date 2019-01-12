#include "AlgorithmOnGPU.hpp"

#include <sstream>

AlgorithmOnGPU::AlgorithmOnGPU(const Text &pattern, const Text &document)
    : Algorithm(pattern, document)
{
    std::vector<cl::Platform> allPlatforms;
    cl::Platform::get(&allPlatforms);
    if (allPlatforms.empty()) throw std::runtime_error{"OpenCL: no platforms found."};

    std::vector<cl::Device> allDevices;
    allPlatforms[0].getDevices(CL_DEVICE_TYPE_ALL, &allDevices);
    if (allDevices.empty()) throw std::runtime_error{"OpenCL: no devices found."};

    context_ = cl::Context{{allDevices[0]}};

    auto kernelCode = readKernelCode(KERNEL_FILE);
    cl::Program::Sources sources = {{kernelCode.c_str(), kernelCode.length()}};

    program_ = cl::Program{context_, sources};
    if (program_.build({allDevices[0]}) != CL_SUCCESS) {
        std::string msg = "OpenCL: program build failed";
        auto buildLog = program_.getBuildInfo<CL_PROGRAM_BUILD_LOG>(allDevices[0]);
        throw std::runtime_error{msg + "\n" + buildLog};
    }

    queue_ = cl::CommandQueue{context_, allDevices[0]};

    documentBuffer_ = cl::Buffer{context_, CL_MEM_READ_WRITE, sizeof(char) * rawDocument_.size()};
    patternBuffer_ = cl::Buffer{context_, CL_MEM_READ_WRITE, sizeof(char) * rawPattern_.size()};
    resultBuffer_ = cl::Buffer{context_, CL_MEM_READ_WRITE, sizeof(char) * lastPossibleIndex_};

    queue_.enqueueWriteBuffer(documentBuffer_, CL_TRUE, 0, sizeof(char) * rawDocument_.size(), rawDocument_.data());
    queue_.enqueueWriteBuffer(patternBuffer_, CL_TRUE, 0, sizeof(char) * rawPattern_.size(), rawPattern_.data());
    queue_.enqueueWriteBuffer(resultBuffer_, CL_TRUE, 0, sizeof(char)*lastPossibleIndex_, occurenceIndexes_.data());
}

std::string AlgorithmOnGPU::readKernelCode(const std::string& fileName) const
{
    std::ifstream codeFile(fileName, std::fstream::in);
    if (codeFile.bad()) throw std::runtime_error("No kernel file");

    std::stringstream kernel_code_stream;
    std::string line;
    while (std::getline(codeFile, line))
        kernel_code_stream << line;
    return kernel_code_stream.str();
}

void AlgorithmOnGPU::runWithoutTimeCheck()
{
    kernel_ = cl::Kernel{program_, KERNEL_PROGRAM_NAME.c_str()};
    cl_ulong patternLen = rawPattern_.size();
    kernel_.setArg(0, documentBuffer_);
    kernel_.setArg(1, patternBuffer_);
    kernel_.setArg(2, patternLen);
    kernel_.setArg(3, resultBuffer_);

    queue_.enqueueNDRangeKernel(kernel_, cl::NullRange, cl::NDRange(lastPossibleIndex_), cl::NullRange);
    queue_.finish();
    queue_.enqueueReadBuffer(resultBuffer_, CL_TRUE, 0, sizeof(char)*lastPossibleIndex_, occurenceIndexes_.data());
}
