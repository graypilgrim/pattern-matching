#include "NaiveAlgorithmOnGPU.hpp"

#include <sstream>

NaiveAlgorithmOnGPU::NaiveAlgorithmOnGPU(const Text &pattern, const Text &document)
    : AlgorithmOnGPU(pattern, document)
{
    KERNEL_PROGRAM_NAME = "naive";
}
