#include <stdexcept>

class ParserException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};
