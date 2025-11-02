#include "attempt.hpp"

Attempt::Attempt(): current{0}, target{1}, name{""}, description{""} {};
Attempt::Attempt(std::string n, std::string desc, int t): current{0}, target{t}, name{n}, description{desc} {};

void Attempt::incCount() { current++; }
void Attempt::decCount() {
    if(current - 1 >= 0) current--;
}

bool Attempt::isCompleted() const noexcept {
    return (target == current);
}

void Attempt::setName(std::string name){ name = name; }
void Attempt::setDescription(std::string desc) {description = desc;}
void Attempt::setTarget(int t) {target = t;}

void Attempt::debug() const {
    std::cout << " Target: " << target
              << " Current: " << current
              << " Attempt name: " << name
              << " Description: " << description << std::endl;
}

Attempt::AttemptData Attempt::serialize() const {
    AttemptData data;
    data.target = target;
    data.current = current;
    data.description = description;
    data.name = name;

    return data;
}

Attempt Attempt::fromData(const AttemptData& data) {
    Attempt atmpt;
    atmpt.target = data.target;
    atmpt.current = data.current;
    atmpt.description = data.description;
    atmpt.name = data.name;

    return atmpt;
}
