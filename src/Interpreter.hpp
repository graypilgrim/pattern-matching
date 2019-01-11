#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <unordered_map>

class Interpreter
{
public:
    Interpreter(int argc, char** argv);

private:
    void printHelpMessage() const;
    void printFileErrorMessage(const std::string &name) const;
    bool checkAlgorithm(const std::string& arg);
    bool checkComputingStyle(const std::string& arg);
    void runAlgorithm(std::ifstream& patternFile, std::ifstream& documentFile) const;

    enum class AlgorithmType
    {naive, winnowing};

    enum class ComputingStyle
    {linear, multithreaded, gpu, shared_mem};

    const std::unordered_map<std::string, ComputingStyle> computingStyles_ = {
        {"linear", ComputingStyle::linear},
        {"multithreaded", ComputingStyle::multithreaded},
        {"gpu", ComputingStyle::gpu},
        {"shared-mem", ComputingStyle::shared_mem}
    };

    const std::string naiveAlgorithmName_ = "naive";
    const std::string winnowingAlgorithmName_ = "winnowing";
    ComputingStyle computingStyle_ = ComputingStyle::linear;
    bool naive_ = true;
};

#endif /* end of include guard: INTERPRETER_HPP */
