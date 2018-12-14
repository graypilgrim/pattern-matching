#ifndef TEXT_HPP
#define TEXT_HPP

#include <fstream>
#include <string>

class Text
{
public:
    Text(std::istream& content);
    std::string getNormalizedContent() const;

private:
    bool isAcceptable(char c);

    std::string normalizedContent_;
};


#endif /* end of include guard: TEXT_HPP */
