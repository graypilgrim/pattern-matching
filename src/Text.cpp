#include "Text.hpp"

#include <sstream>
#include <cctype>
#include <iostream>

Text::Text(std::istream& content, bool removeNewline)
{
    std::ostringstream res;
    while (!content.eof()) {
        char c = content.get();
        if (isalpha(c))
            res << myTolower(c);
        else if (c == '\n' && removeNewline)
            continue;
        else if (isgraph(c) || isspace(c))
            res << c;
    }
    normalizedContent_ = res.str();
    std::cout << normalizedContent_ << std::endl;
}

std::string Text::getNormalizedContent() const
{
    return normalizedContent_;
}

unsigned char Text::myTolower(unsigned char ch)
{
    return static_cast<unsigned char>(std::tolower(static_cast<unsigned char>(ch)));
}
