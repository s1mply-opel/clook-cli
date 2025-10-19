#include "tests/test_framework.hpp"

std::vector<TestEntry>& getTestRegistry() {
    static std::vector<TestEntry> registry;
    return registry;
}

void runAllTests(const std::string& suiteFilter){
    auto& tests = getTestRegistry();
    int passed = 0;
    int total = 0;

    std::cout << "=== Running All Tests === \n\n";

    for (auto& t: tests) {
        if (!suiteFilter.empty() && t.suite != suiteFilter)
            continue;

        std::cout << "[" << std::left << t.suite << "] "<< t.name << ":" << std::endl;
                  
        bool ok = t.func();
        if(ok) {
            // std::cout << "\033[32mPassed\033[0m\n";
            passed++;
        } else {
            // std::cout << "\033[31mFailed\033[0m\n";
        }
        total++;
    }

    std::cout << "\nSummary: " << passed << "/" << total << " passed.\n";
}