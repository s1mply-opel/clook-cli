#pragma once
#include "milestone.hpp"
#include "commons.hpp"

class MilestoneManager {
public:
    struct MilestoneManagerData {
        std::vector<Milestone::MilestoneData> milestones;
        bool running;
        size_t selected;
    };

    MilestoneManager() = default;
    void run(); // main interactive loop

    MilestoneManagerData serialize() const;
    static MilestoneManager fromData(const MilestoneManagerData&);

    std::string getCurrentMilestoneName() const {
        if(selected < milestones.size()){
            return milestones[selected].get()->getName();
        } else {
            return std::string("Not selected");
        }
    }

private:
    std::vector<std::unique_ptr<Milestone>> milestones;
    bool running{true};
    size_t selected {0};
    // Internal helpers
    void showMainMenu() const;
    void showMilestoneMenu(Milestone& m) const;
    void showAttemptMenu() const;

    void handleMainCommand(const std::string& cmd);
    void handleMilestoneCommand(Milestone& m, const std::string& cmd);
};
