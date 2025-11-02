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

private:
    std::vector<std::unique_ptr<Milestone>> milestones;
    bool running{true};
    size_t selected {0};
    // Internal helpers
    void showMainMenu() const;
    void showMilestoneMenu(Milestone& m) const;

    void handleMainCommand(const std::string& cmd);
    void handleMilestoneCommand(Milestone& m, const std::string& cmd);
};
