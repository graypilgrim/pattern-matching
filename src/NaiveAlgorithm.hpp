#ifndef NAIVE_ALGORITHM_HPP
#define NAIVE_ALGORITHM_HPP

#include "Algorithm.hpp"

class NaiveAlgorithm : public Algorithm
{
public:
    using Algorithm::Algorithm;

private:
    void runWithoutTimeCheck();

};

#endif /* end of include guard: NAIVE_ALGORITHM_HPP */
