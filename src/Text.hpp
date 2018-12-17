#ifndef TEXT_HPP
#define TEXT_HPP

#include <fstream>
#include <string>

class Text
{
public:
    Text(std::istream& content, bool removeNewline);
    std::string getNormalizedContent() const;

private:
    unsigned char myTolower(unsigned char ch);

    std::string normalizedContent_;
};


#endif /* end of include guard: TEXT_HPP */
