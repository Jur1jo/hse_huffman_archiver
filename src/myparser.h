#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

class MyParser {
public:
    MyParser(int argc, char* argv[]);
    void AddParameter(std::string message);
    void PrintHelp(std::ostream& out) const;
    const std::vector<std::string>& GetArgument(char c) const;
    const bool HasArgument(char c) const;

private:
    std::string message_;
    std::unordered_map<char, std::vector<std::string>> arguments_;
};
