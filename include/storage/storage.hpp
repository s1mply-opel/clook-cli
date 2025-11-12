#pragma once
#include "milestone.hpp"
#include "attempt.hpp"
#include "milestoneManager.hpp"
#include <cstdint>

void saveAttemptToStream(const Attempt::AttemptData &a, std::ofstream &out);
void saveMilestoneToStream(const Milestone::MilestoneData &m, std::ofstream &out);
void saveMilestoneManager(const MilestoneManager::MilestoneManagerData& mm, const std::string& filename);
void safeSave(const MilestoneManager::MilestoneManagerData &data, const std::string &filename);

Attempt::AttemptData loadAttemptFromStream(std::ifstream &in);
Milestone::MilestoneData loadMilestoneFromStream(std::ifstream &in);
MilestoneManager::MilestoneManagerData loadMilestoneManager(const std::string &filename);
