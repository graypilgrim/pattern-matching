#include "AlgorithmOnGPU.hpp"

#include <sstream>

AlgorithmOnGPU::AlgorithmOnGPU(const Text &pattern, const Text &document)
    : Algorithm(pattern, document)
{
    setUp();
}

void AlgorithmOnGPU::setUp()
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
