#ifndef WINNOWING_ALGORITHM_WITH_MPI
#define WINNOWING_ALGORITHM_WITH_MPI

#include <mpi.h>

#include "WinnowingAlgorithm.hpp"

class WinnowingAlgorithmWithMPI : public WinnowingAlgorithm
{
public:
    WinnowingAlgorithmWithMPI(const Text &pattern, const Text &document);
    virtual ~WinnowingAlgorithmWithMPI() = default;

private:
    void runWithoutTimeCheck() override;
};

#endif
