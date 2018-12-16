#ifndef PARALLEL_NAIVE_ALGORITHM
#define PARALLEL_NAIVE_ALGORITHM

#include "ParallelAlgorithm.hpp"
#include "NaiveAlgorithm.hpp"

class ParallelNaiveAlgorithm : public ParallelAlgorithm, public NaiveAlgorithm
{
public:
    ParallelNaiveAlgorithm(const Text &pattern, const Text &document, size_t threadsNum);

private:
    void runWithoutTimeCheck() override;

};

#endif /* end of include guard: PARALLEL_NAIVE_ALGORITHM */
