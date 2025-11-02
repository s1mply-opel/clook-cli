// File: exceptions.hpp
#pragma once
#include <stdexcept>
#include <string>

namespace Clook::exceptions {

    // Base class for all project-specific exceptions
    class ProjectError : public std::runtime_error {
    public:
        explicit ProjectError(const std::string& msg)
            : std::runtime_error("ProjectError: " + msg) {}
    };

    // Specific exceptions
    class InvalidConstructorError : public ProjectError {
    public:
        explicit InvalidConstructorError(const std::string& msg)
            : ProjectError("Invalid constructor arguments: " + msg) {}
    };

    class InvalidStateError : public ProjectError {
    public:
        explicit InvalidStateError(const std::string& msg)
            : ProjectError("Invalid state: " + msg) {}
    };

    class DependencyMissingError : public ProjectError {
    public:
        explicit DependencyMissingError(const std::string& msg)
            : ProjectError("Missing dependency: " + msg) {}
    };

} // namespace Clook::exceptions
