#ifndef DOMAIN_EXCEPTIONS_H
#define DOMAIN_EXCEPTIONS_H

#include <stdexcept>
#include <string>

class ValidationException : public std::runtime_error {
public:
    explicit ValidationException(const std::string& message)
        : std::runtime_error(message) {}
};

class DuplicateEntryException : public std::runtime_error {
public:
    explicit DuplicateEntryException(const std::string& message)
        : std::runtime_error(message) {}
};

class NotFoundException : public std::runtime_error {
public:
    explicit NotFoundException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif // DOMAIN_EXCEPTIONS_H
