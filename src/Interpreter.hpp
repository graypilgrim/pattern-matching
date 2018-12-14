#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>

class Interpreter
{
public:
    Interpreter(int argc, char** argv);

private:
    void printHelpMessage() const;
    void printHelpMessageWithError(const std::string &name) const;
    void printFileErrorMessage(const std::string &name) const;
    bool checkAlgorithm(const std::string& arg);
    bool checkParallelity(const std::string& arg);

    const std::string naiveAlgorithmName_ = "naive";
    const std::string winnowingAlgorithmName_ = "winnowing";
    const std::string parallellyMarker_ = "p";
    const std::string nonParallellyMarker_ = "np";
    const int argNumber_ = 5;

    bool naive = true;
    bool parallelly = false;
};

#endif /* end of include guard: INTERPRETER_HPP */
