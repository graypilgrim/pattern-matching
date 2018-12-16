#ifndef NAIVE_ALGORITHM_HPP
#define NAIVE_ALGORITHM_HPP

#include "Algorithm.hpp"

class NaiveAlgorithm : public virtual Algorithm
{
public:
    using Algorithm::Algorithm;
    virtual ~NaiveAlgorithm() = default;

private:
    void runWithoutTimeCheck() override;

};

#endif /* end of include guard: NAIVE_ALGORITHM_HPP */
