#include "StringReplacer.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

StringReplacer::StringReplacer(const std::string& filename, const std::string& s1, const std::string& s2)
    : filename(filename), s1(s1), s2(s2) {}

bool StringReplacer::replaceAndSave() {
      std::ifstream inputFile(filename.c_str());
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string content = buffer.str();
    inputFile.close();

    std::string newContent = replaceOccurrences(content);

    std::ofstream outputFile((filename + ".replace").c_str());
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not create output file " << filename + ".replace" << std::endl;
        return false;
    }
    outputFile << newContent;
    outputFile.close();

    return true;
}

std::string StringReplacer::replaceOccurrences(const std::string& content) {
    std::string result = content;
    size_t pos = 0;

    while ((pos = result.find(s1, pos)) != std::string::npos) {
        result.erase(pos, s1.length());
        result.insert(pos, s2);
        pos += s2.length();
    }

    return result;
}