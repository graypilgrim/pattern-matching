#ifndef NAIVE_ALGORITHM_ON_GPU_HPP
#define NAIVE_ALGORITHM_ON_GPU_HPP

#include "Algorithm.hpp"

class NaiveAlgorithmOnGPU : public virtual Algorithm
{
public:
    using Algorithm::Algorithm;
    virtual ~NaiveAlgorithmOnGPU() = default;

private:
    void runWithoutTimeCheck() override;

};

#endif /* end of include guard: NAIVE_ALGORITHM_ON_GPU_HPP */
