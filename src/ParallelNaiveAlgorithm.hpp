#ifndef PARALLEL_NAIVE_ALGORITHM
#define PARALLEL_NAIVE_ALGORITHM

#include "Algorithm.hpp"

class ParallelNaiveAlgorithm : public Algorithm
{
public:
    using Algorithm::Algorithm;

private:
    void runWithoutTimeCheck();

};

#endif /* end of include guard: PARALLEL_NAIVE_ALGORITHM */
