#include "Interpreter.hpp"

#include "Text.hpp"
#include "SequentialNaiveAlgorithm.hpp"
#include "MultithreadedNaiveAlgorithm.hpp"
#include "WinnowingAlgorithm.hpp"
#include "MultithreadedWinnowingAlgorithm.hpp"
#include "NaiveAlgorithmOnGPU.hpp"
#include "WinnowingAlgorithmOnGPU.hpp"

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <memory>

Interpreter::Interpreter(int argc, char** argv)
{
    size_t all = 0;
    bool argumentsRet = true;
    std::ifstream patternFile;
    std::ifstream documentFile;
    int c;
    while((c = getopt(argc, argv, "a:c:p:d:t:"))!= -1)
    {
        switch(c)
        {
        case 'a':
            argumentsRet = checkAlgorithm(optarg);
            ++all;
            break;
        case 'c':
            argumentsRet = checkComputingStyle(optarg);
            ++all;
            break;
        case 'p':
            patternFile.open(optarg);
            if (!patternFile.good()) {
                printFileErrorMessage(optarg);
                argumentsRet = false;
            }
            ++all;
            break;
        case 'd':
            documentFile.open(optarg);
            if (!documentFile.good()) {
                printFileErrorMessage(optarg);
                argumentsRet = false;
            }
            ++all;
            break;
        case 't':
            threadsNo_ = std::stoi(optarg);
            break;
        default:
            printHelpMessage();
        }
    }

    if (all != 4) {
        printHelpMessage();
        return;
    }

    if (argumentsRet) runAlgorithm(patternFile, documentFile);
}

void Interpreter::printHelpMessage() const
{
    std::cout << "Invalid usage, options are:" << std::endl;
    std::cout << "\talgorithm:\t\t-a {" << naiveAlgorithmName_ << ", " << winnowingAlgorithmName_ << "}" << std::endl;
    std::cout << "\tcomputing method:\t-c {";
    for (auto it = computingStyles_.begin(); it != computingStyles_.end(); ++it) {
        std::cout << it->first;
        if (std::next(it, 1) != computingStyles_.end())
            std::cout << ", ";
    }
    std::cout << "}" << std::endl;
    std::cout << "\tpattern file:\t\t-p FILENAME" << std::endl;
    std::cout << "\tdocument file:\t\t-d FILENAME" << std::endl;

}

void Interpreter::printFileErrorMessage(const std::string &name) const
{
    std::cout << "Cannot open " << name << " file" << std::endl;
}

bool Interpreter::checkAlgorithm(const std::string& arg)
{
    if (arg == naiveAlgorithmName_) {
        naive_ = true;
    } else if (arg == winnowingAlgorithmName_) {
        naive_ = false;
    } else {
        printHelpMessage();
        return false;
    }
    return true;
}

bool Interpreter::checkComputingStyle(const std::string& arg)
{
    auto ret = computingStyles_.find(arg);
    if (ret == computingStyles_.end()) {
        printHelpMessage();
        return false;
    }
    computingStyle_ = ret->second;
    return true;
}

void Interpreter::runAlgorithm(std::ifstream& patternFile, std::ifstream& documentFile)
{
    Text pattern{patternFile, true};
    Text document{documentFile, false};
    switch (computingStyle_)
    {
    case ComputingStyle::sequential:
        if (naive_)
            createAndRun<SequentialNaiveAlgorithm>(pattern, document);
        else
            createAndRun<WinnowingAlgorithm>(pattern, document);
        break;
    case ComputingStyle::multithreaded:
        if (naive_)
            createAndRunMultithreaded<MultithreadedNaiveAlgorithm>(pattern, document, threadsNo_);
        else
            createAndRunMultithreaded<MultithreadedWinnowingAlgorithm>(pattern, document, threadsNo_);
        break;
    case ComputingStyle::gpu:
        if (naive_)
            createAndRun<NaiveAlgorithmOnGPU>(pattern, document);
        else
            createAndRun<WinnowingAlgorithmOnGPU>(pattern, document);
        break;
    default:
        /* code */
        break;
    }
}
