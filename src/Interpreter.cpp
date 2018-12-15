#include "Interpreter.hpp"

#include "Text.hpp"
#include "NaiveAlgorithm.hpp"
#include "ParallelNaiveAlgorithm.hpp"

#include <iostream>
#include <fstream>

Interpreter::Interpreter(int argc, char** argv)
{
    if (argc == 1) {
        printHelpMessage();
        return;
    }

    if (argc != argNumber_) {
        printHelpMessage();
        return;
    }

    if(!checkAlgorithm(argv[1])) {
        printHelpMessageWithError(argv[1]);
        return;
    }

    if(!checkParallelity(argv[2])) {
        printHelpMessageWithError(argv[2]);
        return;
    }

    std::ifstream patternFile{argv[3]};
    if (!patternFile.good()) {
        printFileErrorMessage(argv[3]);
        return;
    }

    std::ifstream documentFile{argv[4]};
    if (!documentFile.good()) {
        printFileErrorMessage(argv[4]);
        return;
    }

    Text pattern{patternFile};
    // std::cout << pattern.getNormalizedContent() << std::endl;
    Text document{documentFile};
    // std::cout << document.getNormalizedContent() << std::endl;

    NaiveAlgorithm na{pattern, document};
    na.run();
    na.printResults();

    ParallelNaiveAlgorithm pna{pattern, document};
    pna.run();
    pna.printResults();
}

void Interpreter::printHelpMessage() const
{
    std::cout << "Usage: find-pattern {naive / winnowing} {p / np} PATTERN_FILE DOCUMENT_FILE" << std::endl;
}

void Interpreter::printHelpMessageWithError(const std::string &name) const
{
    std::cout << "Invalid argument:" << name << std::endl;
    printHelpMessage();
}

void Interpreter::printFileErrorMessage(const std::string &name) const
{
    std::cout << "Cannot open " << name << " file" << std::endl;
}

bool Interpreter::checkAlgorithm(const std::string& arg)
{
    if (arg == naiveAlgorithmName_) {
        naive = true;
    } else if (arg == winnowingAlgorithmName_) {
        naive = false;
    } else {
        printHelpMessage();
        return false;
    }
    return true;
}

bool Interpreter::checkParallelity(const std::string& arg)
{
    if (arg == parallellyMarker_) {
        parallelly = true;
    } else if (arg == nonParallellyMarker_) {
        parallelly = false;
    } else {
        printHelpMessage();
        return false;
    }
    return true;
}
