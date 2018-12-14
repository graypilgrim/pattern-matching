#include "Text.hpp"

#include <sstream>
#include <cctype>

namespace {
char my_tolower(char ch)
{
    return static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
}
}

Text::Text(std::istream& content)
{
    std::ostringstream res;
    while (!content.eof()) {
        unsigned char c = content.get();
        if (isAcceptable(c))
            res << my_tolower(c);
    }
    normalizedContent_ = res.str();
}

std::string Text::getNormalizedContent() const
{
    return normalizedContent_;
}

bool Text::isAcceptable(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
