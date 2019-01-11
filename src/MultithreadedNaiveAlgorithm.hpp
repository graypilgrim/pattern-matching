#ifndef MULTITHREADED_NAIVE_ALGORITHM
#define MULTITHREADED_NAIVE_ALGORITHM

#include "MultihreadedAlgorithm.hpp"
#include "SequentialNaiveAlgorithm.hpp"

class MultithreadedNaiveAlgorithm : public MultihreadedAlgorithm
{
public:
    MultithreadedNaiveAlgorithm(const Text &pattern, const Text &document, size_t threadsNum);

private:
    void runWithoutTimeCheck() override;

};

#endif /* end of include guard: MULTITHREADED_NAIVE_ALGORITHM */
