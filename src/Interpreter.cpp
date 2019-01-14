#include "Interpreter.hpp"

#include "Text.hpp"
#include "NaiveAlgorithmWithMPI.hpp"
#include "WinnowingAlgorithmWithMPI.hpp"
#include "utils.hpp"

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
    while((c = getopt(argc, argv, "a:p:d:"))!= -1)
    {
        switch(c)
        {
        case 'a':
            argumentsRet = checkAlgorithm(optarg);
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
        default:
            printHelpMessage();
        }
    }

    if (all != 3) {
        printHelpMessage();
        return;
    }

    if (argumentsRet) runAlgorithm(patternFile, documentFile);
}

void Interpreter::printHelpMessage() const
{
    std::cout << "Invalid usage, options are:" << std::endl;
    std::cout << "\talgorithm:\t\t-a {" << naiveAlgorithmName_ << ", " << winnowingAlgorithmName_ << "}" << std::endl;
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

void Interpreter::runAlgorithm(std::ifstream& patternFile, std::ifstream& documentFile) const
{
    Text pattern{patternFile, true};
    Text document{documentFile, false};
    std::unique_ptr<Algorithm> al;
    if (naive_)
        al = std::make_unique<NaiveAlgorithmWithMPI>(pattern, document);
    else
        al = std::make_unique<WinnowingAlgorithmWithMPI>(pattern, document);

    MPI_Init(nullptr, nullptr);
    al->run();
    MPI_Finalize();
    al->printResults();
}
