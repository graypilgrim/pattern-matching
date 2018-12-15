#include "ParallelNaiveAlgorithm.hpp"

#include <omp.h>

void ParallelNaiveAlgorithm::runWithoutTimeCheck()
{
    #pragma omp parallel for shared(Algorithm::occurenceIndexes)
    for (auto i = 0u; i < rawDocument_.size(); ++i) {
        for (auto k = 0u; k < rawPattern_.size(); ++k) {
            if (rawDocument_[i + k] != rawPattern_[k]) break;

            if (k + 1 == rawPattern_.size())
                occurenceIndexes.push_back(i);
        }
    }
}
