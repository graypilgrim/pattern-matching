#include "WinnowingAlgorithmWithMPI.hpp"

#include "utils.hpp"

#include <functional>

WinnowingAlgorithmWithMPI::WinnowingAlgorithmWithMPI(const Text &pattern, const Text &document)
    : Algorithm(pattern, document), WinnowingAlgorithm(pattern, document)
{}

void WinnowingAlgorithmWithMPI::runWithoutTimeCheck()
{
    auto last = (utils::getProcessorNo() + 1) == utils::getProcessorsCount();

    auto partSize = rawDocument_.size() / utils::getProcessorsCount();
    size_t startIdx = partSize * utils::getProcessorNo();
    size_t endIdx = last ? (lastPossibleIndex_ + 1) : partSize * (utils::getProcessorNo() + 1);

    auto patternHash = std::hash<std::string>{}(rawPattern_);

    for (auto i = startIdx; i < endIdx; ++i) {
        auto nGramHash = std::hash<std::string>{}(rawDocument_.substr(i, nGramSize_));
        if (patternHash == nGramHash) occurenceIndexes_[i] = 1;
    }

    if (utils::getProcessorNo() != 0) {
        utils::mpiSend(occurenceIndexes_.data() + startIdx, endIdx - startIdx, 0);
    } else {
        std::vector<MPI_Request> requests{utils::getProcessorsCount()};

        for (auto i = 1; i < utils::getProcessorsCount(); ++i ) {
            size_t start = partSize * i;
            size_t end = (i + 1) == utils::getProcessorsCount() ? (lastPossibleIndex_ + 1) : partSize * (i + 1);
            utils::mpiIrecv(occurenceIndexes_.data() + start, end - start, i, requests.data());

        }
    }
}
