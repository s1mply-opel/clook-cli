#include "storage/storage.hpp"
#include <fstream>

void writeString(std::ofstream& out, const std::string& s) {
    size_t len = s.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(s.data(), len);
}

std::string readString(std::ifstream& in) {
    size_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    std::string s(len, '\0');
    in.read(&s[0], len);
    return s;
}


void saveAttemptToStream(const Attempt::AttemptData& a, std::ofstream& out) {
    out.write(reinterpret_cast<const char *>(&a.target), sizeof(a.target));
    out.write(reinterpret_cast<const char *>(&a.current), sizeof(a.current));
    writeString(out, a.name);
    writeString(out, a.description);
}

void saveMilestoneToStream(const Milestone::MilestoneData& m, std::ofstream& out) {
    writeString(out, m.name);
    writeString(out, m.description);

    uint64_t loopDuration = static_cast<uint64_t>(m.loopDuration);
    out.write(reinterpret_cast<const char*>(&loopDuration), sizeof(loopDuration));

    uint64_t activeAttemptIndex = static_cast<uint64_t>(m.activeAttemptIndex);
    out.write(reinterpret_cast<const char*>(&activeAttemptIndex), sizeof(activeAttemptIndex));

    uint64_t numAttempts = m.attempts.size();
    out.write(reinterpret_cast<const char*>(&numAttempts), sizeof(numAttempts));
    for (const auto& a: m.attempts) {
        saveAttemptToStream(a, out);
    }
}

void saveMilestoneManager(const MilestoneManager::MilestoneManagerData& mm, const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);

    uint64_t selected = static_cast<uint64_t>(mm.selected);
    out.write(reinterpret_cast<const char*>(&selected), sizeof(selected));

    uint8_t runningByte = mm.running ? 1 : 0;
    out.write(reinterpret_cast<const char*>(&runningByte), sizeof(runningByte));

    uint64_t numMilestones = mm.milestones.size();
    out.write(reinterpret_cast<const char*>(&numMilestones), sizeof(numMilestones));
    for(const auto& m: mm.milestones) {
        saveMilestoneToStream(m, out);
    }
}

MilestoneManager::MilestoneManagerData loadMilestoneManager(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    MilestoneManager::MilestoneManagerData data;

    uint64_t selected;
    in.read(reinterpret_cast<char*>(&selected), sizeof(selected));
    data.selected = static_cast<size_t>(selected);

    uint8_t runningByte;
    in.read(reinterpret_cast<char*>(&runningByte), sizeof(runningByte));
    data.running = runningByte != 0;

    uint64_t numMilestones;
    in.read(reinterpret_cast<char*>(&numMilestones), sizeof(numMilestones));
    data.milestones.resize(numMilestones);

    for (size_t i = 0; i < numMilestones; i++) {
        data.milestones[i] = loadMilestoneFromStream(in);
    }

    return data;
}

Milestone::MilestoneData loadMilestoneFromStream(std::ifstream &in) {
    Milestone::MilestoneData data;
    data.name = readString(in);
    data.description = readString(in);

    uint64_t loopDuration;
    in.read(reinterpret_cast<char*>(&loopDuration), sizeof(loopDuration));
    data.loopDuration = static_cast<int>(loopDuration);

    uint64_t activeAttemptIndex;
    in.read(reinterpret_cast<char*>(&activeAttemptIndex), sizeof(activeAttemptIndex));
    data.activeAttemptIndex = static_cast<int>(activeAttemptIndex);
    
    uint64_t numAttempts;
    in.read(reinterpret_cast<char*>(&numAttempts), sizeof(numAttempts));
    data.attempts.resize(numAttempts);

    for (size_t i = 0; i < numAttempts; i++) {
        data.attempts[i] = loadAttemptFromStream(in);
    }

    return data;
}

Attempt::AttemptData loadAttemptFromStream(std::ifstream &in) {
    Attempt::AttemptData data;

    in.read(reinterpret_cast<char*>(&data.target), sizeof(data.target));
    in.read(reinterpret_cast<char*>(&data.current), sizeof(data.current));
    data.name = readString(in);
    data.description = readString(in);

    return data;
}
