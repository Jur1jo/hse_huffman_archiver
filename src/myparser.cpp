#include "myparser.h"
#include "parserexception.h"

void MyParser::AddParameter(std::string message) {
    message_ += message + "\n";
}

void MyParser::PrintHelp(std::ostream& out) const {
    out << message_;
}

const std::vector<std::string>& MyParser::GetArgument(char c) const {
    return arguments_.at(c);
}

MyParser::MyParser(int argc, char* argv[]) {
    for (size_t i = 1; i < argc;) {
        const auto s = argv[i];
        if (s[0] == '-') {
            arguments_[s[1]] = {};
            ++i;
            while (i < argc && argv[i][0] != '-') {
                arguments_[s[1]].emplace_back(argv[i]);
                ++i;
            }
        } else {
            throw ParserException("Every arguments should starts from -");
        }
    }
}

const bool MyParser::HasArgument(char c) const {
    return arguments_.count(c);
}
