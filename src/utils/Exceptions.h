#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class CapacityExceededException : public std::runtime_error {
public:
    explicit CapacityExceededException(const std::string& courseCode)
        : std::runtime_error("Capacity exceeded for course: " + courseCode)
    {}
};

#endif // EXCEPTIONS_H
