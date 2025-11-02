#pragma once
#include "commons.hpp"

<<<<<<< HEAD
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
=======
// class Notes;

class Attempt{
public:
    struct AttemptData {
        int target;
        int current;
        std::string name;
        std::string description;
    };

    Attempt();
    Attempt(std::string n, std::string desc, int t);

    void incCount();
    void decCount();
    bool isCompleted() const noexcept;

    void setName(std::string);
    void setDescription(std::string);
    void setTarget(int);

    
    const std::string &getName() const noexcept { return name; }
    const std::string &getDescription() const noexcept { return description; }
    int getTarget() const noexcept { return target; }
    int getCurrent() const noexcept { return current; }
    
    
    void debug() const;
    
    AttemptData serialize() const;
    static Attempt fromData(const AttemptData&);


    // Notes
    // void addNote(const std::string &text);
    // const std::vector<std::unique_ptr<Notes>> &getNotes() const noexcept { return notes; }
private:
    int target{1};
    int current{0};
    std::string name;
    std::string description;

    // std::vector<std::unique_ptr<Notes>> notes;
>>>>>>> dev
};