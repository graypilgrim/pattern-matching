#ifndef WINNOWING_ALGORITHM_HPP
#define WINNOWING_ALGORITHM_HPP

#include "Algorithm.hpp"

#include <string>

class WinnowingAlgorithm : public virtual Algorithm
{
public:
    WinnowingAlgorithm(const Text &pattern, const Text &document);
    void runWithoutTimeCheck() override;

protected:
    const size_t nGramSize_ = 0;
    const size_t documentLastIndex_ = 0;
};

#endif /* end of include guard: WINNOWING_ALGORITHM_HPP */
