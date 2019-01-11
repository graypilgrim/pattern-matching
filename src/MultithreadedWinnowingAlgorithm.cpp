#include "MultithreadedWinnowingAlgorithm.hpp"

MultithreadedWinnowingAlgorithm::MultithreadedWinnowingAlgorithm(const Text &pattern, const Text &document, size_t threadsNum)
    : Algorithm(pattern, document), MultihreadedAlgorithm(pattern, document, threadsNum), WinnowingAlgorithm(pattern, document)
{}

void MultithreadedWinnowingAlgorithm::runWithoutTimeCheck()
{
    auto patternHash = std::hash<std::string>{}(rawPattern_);
    omp_set_num_threads(threadsNum_);

    #pragma omp parallel for shared(rawDocument_, patternHash)
    for (auto i = 0u; i < documentLastIndex_; ++i) {
        auto nGramHash = std::hash<std::string>{}(rawDocument_.substr(i, nGramSize_));
        if (patternHash == nGramHash) {
            #pragma omp critical
            occurenceIndexes.push_back(i);
        }
    }
}
