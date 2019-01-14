#ifndef NAIVE_ALGORITHM_WITH_MPI
#define NAIVE_ALGORITHM_WITH_MPI

#include <mpi.h>

#include "Algorithm.hpp"

class NaiveAlgorithmWithMPI : public Algorithm
{
public:
    using Algorithm::Algorithm;
    virtual ~NaiveAlgorithmWithMPI() = default;

private:
    void runWithoutTimeCheck() override;
};

#endif
