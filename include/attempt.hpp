#pragma once
#include "commons.hpp"

class Attempt{
    public:
        Attempt();
        Attempt(int t);
        Attempt(std::string);
        Attempt(std::string, int t);
        void incCount();
        void decCount();
        bool completed();
        void debug();

        const std::string getName();
        const int getTarget();
        const int getCurrent();

    private:
        int target;
        int current;
        std::string name;
};