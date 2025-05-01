#include "Stronghold.h"
#include <iostream>
#include <cstdlib>

Leader::Leader(const std::string& name, double popularity, double level)
    : name_(name), popularity_(popularity), leadershipLevel_(level), isAlive_(true) {
}

void Leader::improveLeadership(double amount) {
    leadershipLevel_ += amount;
    if (leadershipLevel_ > 1.0) leadershipLevel_ = 1.0;
    std::cout << "[Leader] Leadership improved to " << leadershipLevel_ << "\n";
}

void Leader::changePopularity(double delta) {
    popularity_ += delta;
    if (popularity_ > 1.0) popularity_ = 1.0;
    if (popularity_ < 0.0) popularity_ = 0.0;
    std::cout << "[Leader] Popularity is now " << popularity_ << "\n";
}

void Leader::kill() {
    isAlive_ = false;
    std::cout << "[Leader] The leader has died.\n";
}

void Leader::electNewLeader(const std::string& newName) {
    name_ = newName;
    popularity_ = 0.5;
    leadershipLevel_ = 0.5;
    isAlive_ = true;
    std::cout << "[Leader] A new leader has been elected: " << name_ << "\n";
}

void Leader::simulateCoup() {
    if (popularity_ < 0.3 && (rand() % 100) < 20) {
        std::cout << "[Coup] A coup has occurred due to low popularity!\n";
        kill();
    }
    else {
        std::cout << "[Coup] No coup occurred.\n";
    }
}

void Leader::displayStatus() const {
    std::cout << "\n[Leader Status]\n"
        << " Name: " << name_ << "\n"
        << " Popularity: " << popularity_ << "\n"
        << " Leadership: " << leadershipLevel_ << "\n"
        << " Status: " << (isAlive_ ? "Alive" : "Deceased") << "\n";
}

void Leader::serialize(std::ostream& os) const {
    os << name_ << "\n"
        << popularity_ << " " << leadershipLevel_ << " " << isAlive_ << "\n";
}

void Leader::deserialize(std::istream& is) {
    std::getline(is >> std::ws, name_);
    is >> popularity_ >> leadershipLevel_ >> isAlive_;
}

double Leader::getPopularity() const { return popularity_; }
double Leader::getLeadershipLevel() const { return leadershipLevel_; }
bool Leader::isLeaderAlive() const { return isAlive_; }
