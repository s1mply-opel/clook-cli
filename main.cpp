#include "milestoneManager.hpp"
#include "storage/storage.hpp"
#include "commons.hpp"
#include <filesystem>
#include <iostream>

int main() {
    ensureSaveFolderExists();
    MilestoneManager mm;

    // Load previous state
    MilestoneManager::MilestoneManagerData prevData;
    try {
        prevData = loadMilestoneManager(SAVE_FILE_PATH.string());
        mm = MilestoneManager::fromData(prevData);
    } catch (...) {
        std::cout << "2\n";
    }

    // Run manager logic
    mm.run();

    // Save updated state
    MilestoneManager::MilestoneManagerData newData = mm.serialize();
    saveMilestoneManager(newData, SAVE_FILE_PATH.string());

    std::cout << "Saved to " << SAVE_FILE_PATH << std::endl;
    return 0;
}
