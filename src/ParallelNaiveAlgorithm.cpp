#include "ParallelNaiveAlgorithm.hpp"

#include <omp.h>

void ParallelNaiveAlgorithm::runWithoutTimeCheck()
{
    omp_set_num_threads(threadsNum_);
    #pragma omp parallel for shared(rawDocument_, rawPattern_)
    for (auto i = 0u; i < rawDocument_.size(); ++i) {
        for (auto k = 0u; k < rawPattern_.size(); ++k) {
            if (rawDocument_[i + k] != rawPattern_[k]) break;

            if (k + 1 == rawPattern_.size()) {
                #pragma omp critical
                occurenceIndexes.push_back(i);
            }
        }
    }
}
