#pragma once
#include "commons.hpp"
#include "attempt.hpp"
#include "timer.hpp"
#include "exceptions.hpp"

class Notes;

class Milestone {    
public:
    struct MilestoneData {
        std::string name;
        std::string description;
        std::vector<Attempt::AttemptData> attempts;
        int activeAttemptIndex{-1};
        int loopDuration{0};
    };

    Milestone(std::string n, std::string desc="");

    Attempt& createAttempt(std::string n, std::string desc, int t);
    
    void listAttempts();

    void selectAttempt(int index);
    void deleteAttempt(int index);
    void startAttempt();
    void pauseAttempt();
    void resumeAttempt();
    void stopAttempt();

    // void addNote(const std::string& text);

    void setSessionDuration(int minutes);

    const std::string& getName() const noexcept { return name; }
    const std::string& getDescription() const noexcept { return description; }
    const int getDuration() const noexcept { return loopDuration; }

    const std::string getAttemptName() const noexcept {
        if (selected < attempts.size()) {
            return attempts[selected].get()->getName();
        } else {
            return std::string("NULL");
        }
    }

    const bool isAttemptSelected() const noexcept { return (selected < attempts.size()); }

    MilestoneData serialize() const;
    static Milestone fromData(const MilestoneData&);
    
private:
    std::string name;
    std::string description;
    std::vector<std::unique_ptr<Attempt>> attempts;
    size_t selected{0};
    int loopDuration {0};

    Attempt* activeAttempt{nullptr};
    std::unique_ptr<Timer> timer;
};