#include "MultihreadedAlgorithm.hpp"

MultihreadedAlgorithm::MultihreadedAlgorithm(const Text &pattern, const Text &document, size_t threadsNum)
    : Algorithm(pattern, document), threadsNum_(threadsNum)
{}
