<<<<<<< HEAD
#include <iostream>
#include <vector>
#include <cassert>
=======
#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <memory>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <limits.h>
#endif

inline std::filesystem::path getExecutablePath() {
    #ifdef _WIN32
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        return std::filesystem::path(buffer).parent_path();
    #else
        char buffer[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", buffer, PATH_MAX);
        if (count == -1)
            throw std::runtime_error("Cannot determine executable path");
        return std::filesystem::path(std::string(buffer, count)).parent_path();
    #endif
}

// Project folder: assumes exe is in bin/, adjust if needed
inline std::filesystem::path PROJECT_FOLDER = getExecutablePath().parent_path();
// Dedicated saves folder
inline std::filesystem::path SAVE_FOLDER = PROJECT_FOLDER / "saves";
// Full save file path
inline std::filesystem::path SAVE_FILE_PATH = SAVE_FOLDER / "milestone_manager.bin";
// Ensure saves folder exists
inline void ensureSaveFolderExists() {
    std::filesystem::create_directories(SAVE_FOLDER);
}


constexpr int SESSION_DURATION = 45; //in minutes;
>>>>>>> dev
