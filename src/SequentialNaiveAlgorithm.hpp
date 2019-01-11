#ifndef LINEAR_NAIVE_ALGORITHM_HPP
#define LINEAR_NAIVE_ALGORITHM_HPP

#include "Algorithm.hpp"

class SequentialNaiveAlgorithm : public virtual Algorithm
{
public:
    using Algorithm::Algorithm;
    virtual ~SequentialNaiveAlgorithm() = default;

private:
    void runWithoutTimeCheck() override;

};

#endif /* end of include guard: LINEAR_NAIVE_ALGORITHM_HPP */
