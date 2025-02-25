#ifndef STRINGREPLACER_HPP
#define STRINGREPLACER_HPP

#include <string>

class StringReplacer {
public:
    StringReplacer(const std::string& filename, const std::string& s1, const std::string& s2);
    bool replaceAndSave();

private:
    std::string filename;
    std::string s1;
    std::string s2;

    std::string replaceOccurrences(const std::string& content);
};

#endif