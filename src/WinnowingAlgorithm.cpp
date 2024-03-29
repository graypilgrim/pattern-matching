#include "WinnowingAlgorithm.hpp"

#include <functional>

WinnowingAlgorithm::WinnowingAlgorithm(const Text &pattern, const Text &document)
    : Algorithm(pattern, document), nGramSize_(rawPattern_.size()), documentLastIndex_(rawDocument_.size() - nGramSize_)
{}

void WinnowingAlgorithm::runWithoutTimeCheck()
{
    auto patternHash = std::hash<std::string>{}(rawPattern_);

    for (auto i = 0u; i < documentLastIndex_; ++i) {
        auto nGramHash = std::hash<std::string>{}(rawDocument_.substr(i, nGramSize_));
        if (patternHash == nGramHash) occurenceIndexes_[i] = 1;
    }
}
