#include "NaiveAlgorithm.hpp"

void NaiveAlgorithm::runWithoutTimeCheck()
{
    for (auto i = 0u; i < rawDocument_.size(); ++i) {
        for (auto k = 0u; k < rawPattern_.size(); ++k) {
            if (rawDocument_[i + k] != rawPattern_[k]) break;

            if (k + 1 == rawPattern_.size())
                occurenceIndexes[i] = 1;
        }
    }
}
