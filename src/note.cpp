#include "note.hpp"

Note::Note(const std::string& text){
    content = text;
}

void Note::edit(const std::string& newText){
    content += newText;
}

// const std::string& getText() const noexcept {
//     return content;
// }