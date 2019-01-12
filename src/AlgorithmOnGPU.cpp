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

    defaultDevice_ = allDevices[0];
    context_ = cl::Context{{defaultDevice_}};

    queue_ = cl::CommandQueue{context_, defaultDevice_};
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
    queue_.finish();
}
