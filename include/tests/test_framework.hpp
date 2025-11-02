#pragma once
#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include <cstring>

<<<<<<< HEAD
#define GREEN "\033[32m"
#define RED "\033[31m"
=======
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define GREY "\033[30m"
>>>>>>> dev
#define RESET "\033[0m"

// --- Test representation ---
struct TestEntry {
    std::string suite;
    std::string name;
    bool (*func)();
};

// --- Registry Access ---
std::vector<TestEntry>& getTestRegistry();

// --- Helpers ---
inline std::string extractSuiteName(const char* filePath) {
    std::string file = filePath;
    // Get filename only
    auto pos = file.find_last_of("/\\");
    if (pos != std::string::npos)
        file = file.substr(pos + 1);
    // Strip prefix "test_" if present
    if (file.rfind("test_", 0) == 0)
        file = file.substr(5);
    // Strip suffix ".cpp" if present
    if (file.size() > 4 && file.substr(file.size() - 4) == ".cpp")
        file = file.substr(0, file.size() - 4);
    // Capitalize first letter
    if (!file.empty())
        file[0] = toupper(file[0]);
    return file;
}

// --- Macros ---
#define REGISTER_TEST(testName)                                                     \
    bool testName();                                                                \
    static bool _registered_##testName = []() {                                     \
        std::string suite = extractSuiteName(__FILE__);                             \
        getTestRegistry().push_back({suite, #testName, testName});                  \
        return true;                                                                \
    }();                                                                            \
    bool testName()

<<<<<<< HEAD
#define TEST(cond, msg, failedPtr)                                                  \
    do {                                                                            \
        if (!(cond)) {                                                              \
            std::cout << "\t" << RED << "[FAIL] " << RESET << msg << std::endl;     \
            (*failedPtr)++;                                                         \
        }                                                                           \
        else {                                                                      \
            std::cout << "\t" << GREEN << "[PASS] " << RESET << std::endl;          \
=======
#define TEST(targ, cond, msg, failedPtr)                                            \
    do {                                                                            \
        constexpr int WIDTH = 30;                                                   \
        if (!(cond)) {                                                              \
            std::cout << GREY << "\t-" << std::left << std::setw(WIDTH) << targ << RESET;           \
            std::cout << RED << " [FAIL] " << RESET << msg << std::endl;            \
            (*failedPtr)++;                                                         \
        }                                                                           \
        else {                                                                      \
            std::cout << "\t-" << std::left << std::setw(WIDTH) << targ;            \
            std::cout << GREEN << " [PASS]" << RESET << std::left << std::endl;     \
>>>>>>> dev
        }                                                                           \
    } while (0)

// void runAllTests();
void runAllTests(const std::string& suiteFilter = "");
