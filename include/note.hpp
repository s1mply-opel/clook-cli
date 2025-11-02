#pragma once
#include "commons.hpp"
#include <ctime>

class Note{
public:
    Note(const std::string& text);

    void edit(const std::string& newText);
    const std::string& getText() const noexcept;
    std::time_t getCreatedAt() const noexcept;
    std::time_t getLastEdited() const noexcept;

    void debug() const;

private:
    int noteId;
    std::time_t createdAt;
    std::time_t lastEdited;
    std::string content;
};