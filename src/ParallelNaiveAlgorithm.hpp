#ifndef PARALLEL_NAIVE_ALGORITHM
#define PARALLEL_NAIVE_ALGORITHM

#include "ParallelAlgorithm.hpp"

class ParallelNaiveAlgorithm : public ParallelAlgorithm
{
public:
    using ParallelAlgorithm::ParallelAlgorithm;

private:
    void runWithoutTimeCheck() override;

};

#endif /* end of include guard: PARALLEL_NAIVE_ALGORITHM */
