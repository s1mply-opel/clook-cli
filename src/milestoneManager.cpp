#include "milestoneManager.hpp"

void MilestoneManager::showMainMenu() const {
    std::cout << "=== Clook: Main Menu ===\n";
    std::cout << "Commands:\n"
              << "  new <name> <desc>     - Create new milestone\n"
              << "  list                  - List all milestones\n"
              << "  delete <index>        - Delete milestone\n"
              << "  select <index>        - Manage milestone\n"
              << "  enter                 - Enter milestone\n"
              << "  help                  - Show commands\n"
              << "  clear                 - Clear screen\n"
              << "  quit | exit           - Exit program\n";
}

void MilestoneManager::showMilestoneMenu(Milestone& m) const {
    std::cout << "=== Milestone: " << m.getName() << " ===\n";
    std::cout << "Commands:\n"
              << "  info                  - Show milestone details\n"
              << "  add <name> <desc> <t> - Add a new attempt\n"
              << "  list                  - List all attempts\n"
              << "  enter                 - Enter attempt menu\n"
              << "  delete <index>        - Delete attempt by index\n"
              << "  select <index>        - Select and manage a specific attempt\n"
              << "  set <minutes>         - Set duration time per loop\n"
              << "  help                  - Show commands\n"
              << "  back                  - Return to main menu\n";
}

void MilestoneManager::showAttemptMenu() const {
    std::cout << "=== Attempt ===\n";
    std::cout << "Commands:\n"
              << " start                     - Start attempt\n"
              << " pause                     - Pause attempt\n"
              << " resume                    - Resume attempt\n"
              << " stop                      - Stop attempt\n"
              << " back                      - Return to milestone menu\n"
              << " help                      - Show all commands\n";
}


void MilestoneManager::run() {
    std::cout << "[Clook] > ";
    running = true;
    while (running) {
        std::string cmd;
        if(!std::getline(std::cin, cmd)) {
            cmd = "exit";
            std::cout << std::endl;
        }
        if (cmd.empty()) {
            std::cout << "[Clook] > ";
            continue;
        } 
        if(cmd == "quit" || cmd == "exit") break;
        handleMainCommand(cmd);
    }
    std::cout << "Goodbye!\n";
}


void MilestoneManager::handleMainCommand(const std::string& cmd) {
    std::istringstream iss(cmd);
    std::string action;
    iss >> action;

    if (action.empty()) {
        std::cout << "[Milestone: " << getCurrentMilestoneName() << "] > ";
        return;
    }
    
    // Create new milestone
    if(action == "new") {
        std::string name, desc;
        iss >> std::quoted(name) >> std::quoted(desc);
        
        try {
            milestones.push_back(std::make_unique<Milestone>(name, desc));
            std::cout << "Created milestone: " << name << std::endl;
        } catch (const Clook::exceptions::ProjectError& e) {
            std::cerr << e.what() << std::endl;
        }
    
    } else if(action == "list"){
        if (milestones.empty()) {
            std::cout << "No milestones yet, Start a new one!" << std::endl;
        } else {
            std::cout << "Milestone" << std::endl;
            for (size_t i = 0; i < milestones.size(); i++){
                std::cout << "  " << i + 1 << ". " << milestones[i]->getName();
                if(milestones[i]->getDescription().empty()) {
                    std::cout << std::endl;
                } else {
                    std::cout << ": " << milestones[i]->getDescription() << std::endl;
                }
            }
        }

    } else if (action == "delete") {
        size_t index; 
        iss >> index;
        index--;

        if (milestones.empty()) {
            std::cout << "Milestones is empty." << std::endl;
        }

        if (index < milestones.size() && index >= 0) {
            try {
                // ? What if can't erase?
                auto name = milestones[index]->getName();
                milestones.erase(milestones.begin() + index);
                std::cout << "Deleted milestone: " << name << std::endl;
            } catch (const Clook::exceptions::ProjectError& e) {
                std::cerr << e.what() << std::endl;
            }
        } else {
            std::cout << "Invalid index." << std::endl;
        }
    } else if (action == "select") {
        size_t index;
        iss >> index;
        index--;

        if (index < milestones.size()) {
            selected = index;
            std::cout << "Milestone: " << milestones[selected].get()->getName() << " selected" << std::endl;
        } else {
            std::cout << "Invalid index." << std::endl;
        }
    } else if (action == "enter") {
        if (selected < milestones.size() && selected >= 0) {
            Milestone& m = *milestones[selected];
            std::string subcmd;

            std::cout << "[Milestone: " << m.getName() << "] > ";
            while (true) {
                if(!std::getline(std::cin , subcmd)) {
                    return;
                }
                if (subcmd == "back") break;
                handleMilestoneCommand(m, subcmd);
            }
        } else {
            std::cout << "Invalid index." << std::endl;
        }
    } else if (action == "help") {
        showMainMenu();
    } else if (action == "clear") {
        std::cout << "\033[2J\033[H";
        std::cout << "[Clook] > ";
        return;
    } 
    else {
        std::cout << "Unknown command. \n";
    }
    std::cout << "[Clook] > ";
} 

void MilestoneManager::handleMilestoneCommand(Milestone& m, const std::string& cmd) {
    std::istringstream iss(cmd);
    std::string action;
    iss >> action;

    if (action == "info") {
        std::cout << m.getName() << ": ";
        std::string desc = m.getDescription();
        if (desc.empty()) {
            std::cout << "No description";
        } else {
            std::cout << desc;
        }
        
        std::cout << " --- Loop Duration: " << m.getDuration() << " minutes." << std::endl; 
    } else if (action == "add") {
        std::string name, desc; int t;
        iss >> std::quoted(name) >> std::quoted(desc) >> t;
        
        // ?? Have to check if successfully created or not. 
        auto atmpt = m.createAttempt(name, desc, t);
        std::cout << "Attempt: " << atmpt.getName() << " successfully created." << std::endl;
    } else if (action == "list") {
        m.listAttempts();
    } else if (action == "select") {
        size_t index; iss >> index;
        m.selectAttempt(index); 
    } else if (action == "enter") { 
        if (!m.isAttemptSelected()) { std::cout << "Select an Attempt first" << std::endl; } 
        else {
            std::string subcmd;
            while (true) {
                std::cout << "[Attempt: " << m.getAttemptName() << "] > ";

                if (!std::getline(std::cin, subcmd)) return;
                if (subcmd.empty()) continue;
                if (subcmd == "back") break;
                
                else if (subcmd == "start") {
                    m.startAttempt();
                } else if (subcmd == "pause") {
                    m.pauseAttempt();
                } else if (subcmd == "resume") {
                    m.resumeAttempt();
                } else if (subcmd == "stop") {
                    m.stopAttempt();
                } else if (subcmd == "help") {
                    showAttemptMenu();
                } else {
                    std::cout << "Invalid command" << std::endl;
                }
            }
        }
    } else if (action == "set") {
        int duration; iss >> duration;
        m.setSessionDuration(duration);
        std::cout << "Loop duration has been set to " << duration << " minutes." << std::endl;
    } else if (action == "help") {
        showMilestoneMenu(m);
    } else if (action == "delete") {
        size_t index; iss >> index;
        m.deleteAttempt(index);
    } else if (action.empty()) {

    }
    
    else {
        std::cout << "Unknown command" << std::endl;
    }
    std::cout << "[Milestone: " << m.getName() << "] > ";
}


MilestoneManager::MilestoneManagerData MilestoneManager::serialize() const {
    MilestoneManagerData data;

    data.running = running;
    data.selected = selected;
    for (auto& it: milestones) {
        data.milestones.push_back(it->serialize());
    }

    return data;
}

MilestoneManager MilestoneManager::fromData(const MilestoneManagerData& data) {
    MilestoneManager mm;

    for (auto it: data.milestones) {
        auto m = Milestone::fromData(it);
        mm.milestones.push_back(std::make_unique<Milestone>(std::move(m)));
    }

    mm.running = data.running;
    mm.selected = data.selected;

    return mm;
}