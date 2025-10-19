#include "attempt.hpp"

Attempt::Attempt(): current{0}, target{1}, name{} {}
Attempt::Attempt(int t): current{0}, target{t}, name{} {}
Attempt::Attempt(std::string n): current{0}, target{1}, name{n} {}
Attempt::Attempt(std::string n, int t): current{0}, target{t}, name{n} {}
void Attempt::incCount() {
    if (current < target) current++;
}
void Attempt::decCount() {
    if (current > 0) current--;
}
bool Attempt::completed() { return current == target; }
void Attempt::debug() {
    std::cout << "target: " << target << " " << " current: " << current << std::endl;
}

const std::string Attempt::getName() {return name;}
const int Attempt::getTarget() {return target;}
const int Attempt::getCurrent() {return current;}
