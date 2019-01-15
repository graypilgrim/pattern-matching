#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "Text.hpp"

#include <string>
#include <unordered_map>
#include <memory>

class Interpreter
{
public:
    Interpreter(int argc, char** argv);

private:
    void printHelpMessage() const;
    void printFileErrorMessage(const std::string &name) const;
    bool checkAlgorithm(const std::string& arg);
    bool checkComputingStyle(const std::string& arg);
    void runAlgorithm(std::ifstream& patternFile, std::ifstream& documentFile);
    template <typename T>
    void createAndRun(const Text &pattern, const Text &document) {
        auto al = std::make_unique<T>(pattern, document);
        al->run();
        al->printResults();
    }
    template <typename T>
    void createAndRunMultithreaded(const Text &pattern, const Text &document, int threadsNo) {
        auto al = std::make_unique<T>(pattern, document, threadsNo);
        al->run();
        al->printResults();
    }

    enum class AlgorithmType
    {naive, winnowing};

    enum class ComputingStyle
    {sequential, multithreaded, gpu, shared_mem};

    const std::unordered_map<std::string, ComputingStyle> computingStyles_ = {
        {"sequential", ComputingStyle::sequential},
        {"multithreaded", ComputingStyle::multithreaded},
        {"gpu", ComputingStyle::gpu},
        {"shared-mem", ComputingStyle::shared_mem}
    };

    const std::string naiveAlgorithmName_ = "naive";
    const std::string winnowingAlgorithmName_ = "winnowing";
    ComputingStyle computingStyle_ = ComputingStyle::sequential;
    bool naive_ = true;
    int threadsNo_ = 1;
};

#endif /* end of include guard: INTERPRETER_HPP */
