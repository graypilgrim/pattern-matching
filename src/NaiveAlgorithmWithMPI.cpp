#include "NaiveAlgorithmWithMPI.hpp"

#include "utils.hpp"

void NaiveAlgorithmWithMPI::runWithoutTimeCheck()
{
    auto last = (utils::getProcessorNo() + 1) == utils::getProcessorsCount();

    auto partSize = rawDocument_.size() / utils::getProcessorsCount();
    size_t startIdx = partSize * utils::getProcessorNo();
    size_t endIdx = last ? (lastPossibleIndex_ + 1) : partSize * (utils::getProcessorNo() + 1);

    for (auto i = startIdx; i < endIdx; ++i) {
        for (auto k = 0u; k < rawPattern_.size(); ++k) {
            if (rawDocument_[i + k] != rawPattern_[k]) break;

            if (k + 1 == rawPattern_.size())
                occurenceIndexes_[i] = 1;
        }
    }

    if (utils::getProcessorNo() != 0) {
        utils::mpiSend(occurenceIndexes_.data() + startIdx, endIdx - startIdx, 0);
    } else {
        MPI_Request requests[utils::getProcessorsCount()];

        for (auto i = 1; i < utils::getProcessorsCount(); ++i ) {
            size_t start = partSize * i;
            size_t end = (i + 1) == utils::getProcessorsCount() ? (lastPossibleIndex_ + 1) : partSize * (i + 1);
            utils::mpiIrecv(occurenceIndexes_.data() + start, end - start, i, requests);

        }
    }
}
