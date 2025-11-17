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

void Milestone::deleteAttempt(int index) {
    index--;
    if (index < attempts.size()) {
        auto name = attempts[index].get()->getName();
        attempts.erase(attempts.begin() + index);
        std::cout << "Removed: " << name << std::endl;
    } else {
        std::cout << "Invalid index" << std::endl;
    } 
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

    std::cout << "Attempts" << std::endl;
    for (size_t i = 0;i < attempts.size(); i++) {
        std::string name, desc;
        int cur, trg;
        name = attempts[i].get()->getName();
        desc = attempts[i].get()->getDescription();
        cur = attempts[i].get()->getCurrent();
        trg = attempts[i].get()->getTarget();

        if (i == selected && timer->isRunning()) {
            if (desc.empty()) {
                std::cout << "  " << i + 1 << ". " << name << " -- " << cur << " / " << trg << " -- Running" << std::endl;
            }
            else {
                std::cout << "  " << i + 1 << ". " << name << " - " << desc << " -- " << cur << " / " << trg << " -- Running" << std::endl;
            }
        } else {
            if (desc.empty()) {
                std::cout << "  " << i + 1 << ". " << name << " -- " << cur << " / " << trg << std::endl;
            }
            else {
                std::cout << "  " << i + 1 << ". " << name << " - " << desc << " -- " << cur << " / " << trg << std::endl;
            }
        }
    }
}

void Milestone::setMilestoneName(std::string newName) {
    name = newName;
}

void Milestone::setAttemptName(std::string newName) {
    if (isAttemptSelected()) {
        activeAttempt->setName(newName);
    } else {
        std::cout << "Select an attempt first!" << std::endl;
    }
}

void Milestone::setAttemptDesc(std::string newDesc) {
    if (isAttemptSelected()) {
        activeAttempt->setDescription(newDesc);
    } else {
        std::cout << "Select an attempt first!" << std::endl;
    }
}

void Milestone::setAttemptTarget(int t) {
    if (isAttemptSelected()) {
        activeAttempt->setTarget(t);
    } else {
        std::cout << "Select an attempt first!" << std::endl;
    }
}

void Milestone::selectAttempt(int index) {
    index--;
    if (index < attempts.size()) {
        selected = index;
        activeAttempt = attempts[index].get();
        std::cout << "Selected: " << activeAttempt->getName() << std::endl;
    } else {
        std::cout << "Invalid index This?" << std::endl;
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
            std::cout << "Attempt: " << activeAttempt->getCurrent() << "/" << activeAttempt->getTarget() << "\n"
                      << "[Attempt: " << activeAttempt->getName() << "2] >";
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

void Milestone::pauseAttempt() { 
    timer->pause(); 
    if(timer->isPaused()) {
        std::cout << "Timer is paused." << std::endl;
    }
}
void Milestone::resumeAttempt() { 
    if(!timer->isRunning()) {
        timer->resume(); 
        std::cout << "Timer has resumed." << std::endl;
        //Todo
        // timer->getRemainingDuration();
    } else {
        std::cout << "Timer is already running." << std::endl;
    }
    
}

Milestone::MilestoneData Milestone::serialize() const {
    MilestoneData data;
    data.name = name;
    data.description = description;
    data.loopDuration = loopDuration;
    
    for(auto& attempt: attempts) {
        data.attempts.push_back(attempt->serialize());
    }

    data.activeAttemptIndex = selected;
    return data;
}

Milestone Milestone::fromData(const MilestoneData& data) {
    Milestone m(data.name, data.description);
    
    for (auto& it: data.attempts) {
        auto a = Attempt::fromData(it);
        m.attempts.push_back(std::make_unique<Attempt>(std::move(a)));
    }

    m.selected = data.activeAttemptIndex;
    if (m.selected < m.attempts.size()) m.activeAttempt = m.attempts[m.selected].get();
    else                                m.activeAttempt = nullptr;

    m.setSessionDuration(data.loopDuration);

    return m;
}