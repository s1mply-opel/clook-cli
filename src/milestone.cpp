#include "milestone.hpp"

using namespace Clook::exceptions;

Milestone::Milestone(std::string n, std::string desc):name{n}, description{desc} {
    if(n.empty()) {
       throw InvalidConstructorError("Name is empty");
    }

    timer = std::make_unique<Timer>();
    timer->setDuration(SESSION_DURATION * 60);
}

void Milestone::setSessionDuration(int minutes) { 
    loopDuration = minutes;
    // timer->setDuration(minutes * 60); 
}

Attempt& Milestone::createAttempt(std::string n, std::string desc,int t) {
    auto attempt = std::make_unique<Attempt>(n, desc, t);
    attempts.push_back(std::move(attempt));
    return *attempts.back();
}

void Milestone::listAttempts() {
    if (attempts.empty()) {
        std::cout << "No attempts, create a new one!" << std::endl;
        return;
    }

    std::cout << "Attempts: " << std::endl;
    for (size_t i = 0;i < attempts.size(); i++) {
        std::cout << i + 1 << ". " << attempts[i].get()->getName() << std::endl;
    }
}

void Milestone::selectAttempt(int index) {
    index--;
    if (index < attempts.size()) {
        activeAttempt = attempts[index].get();
        std::cout << "Selected: " << activeAttempt->getName() << std::endl;
    } else {
        std::cout << "Invalid index" << std::endl;
    }
}

void Milestone::startAttempt(){
    if (!activeAttempt) {
        std::cout << "Select an attempt first!" << std::endl;
        return;
    }
    // Stop any existing timer.
    timer->stop();

    if (loopDuration <= 0) {
        std::cout << "Set a loop duration first!" << std::endl;
        return;
    }
    timer->setDuration(loopDuration * 60);
    // Set timer to incCount Attempt when finished
    timer->setCallback([this]() {
        if(activeAttempt) {
            activeAttempt->incCount();
            //Optional: logs or notification for user
            std::cout << "Attempt: " << activeAttempt->getCurrent() << "/" << activeAttempt->getTarget() << std::endl;
            std::cout << "--> ";
        }
    });
    // Start timer
    timer->start();
    auto now = std::chrono::system_clock::now();
    auto later = now + std::chrono::minutes(loopDuration);
    std::time_t t = std::chrono::system_clock::to_time_t(later);
    std::tm tm = *std::localtime(&t);

    std::cout << "Attempt started! ";
    // ?? Show what time the loop is expected to finish.
    std::cout << "Loop " << activeAttempt->getCurrent() + 1 << " will be finished at "
              << std::put_time(&tm, "%H:%M:%S") << std::endl;
}

void Milestone::stopAttempt() {
    timer->stop();
    activeAttempt = nullptr;
}

void Milestone::pauseAttempt() { timer->pause(); }
void Milestone::resumeAttempt() { timer->resume(); }

// Might need to redo
// void Milestone::addNote(const std::string& text){
//     notes.emplace_back(text);
// }

Milestone::MilestoneData Milestone::serialize() const {
    MilestoneData data;
    data.name = name;
    data.description = description;
    data.loopDuration = loopDuration;
    
    for(auto& attempt: attempts) {
        data.attempts.push_back(attempt->serialize());
    }

    data.activeAttemptIndex = -1;
    // store index of active attempt, or -1 if none
    if (activeAttempt) {
        auto it = std::find_if(attempts.begin(), attempts.end(),
                               [this](const std::unique_ptr<Attempt>& ptr) { return ptr.get() == activeAttempt; });
        data.activeAttemptIndex = (it != attempts.end()) ? std::distance(attempts.begin(), it) : -1;
    }

    return data;
}

Milestone Milestone::fromData(const MilestoneData& data) {
    Milestone m(data.name, data.description);
    
    for (auto& it: data.attempts) {
        auto a = Attempt::fromData(it);
        m.attempts.push_back(std::make_unique<Attempt>(std::move(a)));
    }

    if(data.activeAttemptIndex >= 0) {
        m.selectAttempt(data.activeAttemptIndex);
    }
    m.setSessionDuration(data.loopDuration);

    return m;
}