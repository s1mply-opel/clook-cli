#include "milestoneManager.hpp"
#include "storage/storage.hpp"
#include "commons.hpp"
#include <filesystem>
#include <iostream>
#include <csignal>

MilestoneManager* global_mm = nullptr;

void handleExitSignal(int signum) {
    std::cout << "\n[Info] Clook received signal " << signum << ", saving progress...\n";
    if (global_mm) {
        try {
            auto data = global_mm->serialize();
            safeSave(data, SAVE_FILE_PATH.string());
            std::cout << "[Info] Emergency save complete.\n";
        } catch (const std::exception& e) {
            std::cerr << "[Error] Failed to save during shutdown: " << e.what() << "\n";
        }
    }
    std::_Exit(0); // Immediately terminate without unwinding (safe for signal)
}

int main() {
    ensureSaveFolderExists();
    MilestoneManager mm;
    global_mm = &mm;

    std::signal(SIGINT, handleExitSignal);
    std::signal(SIGTERM, handleExitSignal);
    std::signal(SIGHUP, handleExitSignal);

    // Load previous state
    MilestoneManager::MilestoneManagerData prevData;
    try {
        prevData = loadMilestoneManager(SAVE_FILE_PATH.string());
        mm = MilestoneManager::fromData(prevData);
    } catch (...) {
        std::cout << "[Info] No previous save found or load failed.\n";
    }

    // Run manager logic
    mm.run();

    // Save updated state
    MilestoneManager::MilestoneManagerData newData = mm.serialize();
    safeSave(newData, SAVE_FILE_PATH.string());

    return 0;
}
