#include "Stronghold.h"
#include <iostream>

// ─── Army definitions ────────────────────────────────────────────────────────

Army::Army(int initial)
    : totalSoldiers_(initial),
    trainedSoldiers_(0),
    morale_(0.75),     // start reasonably high
    payDue_(0.0)
{
    if (initial < 0) throw "Initial army size cannot be negative";
}

void Army::recruit(int number, int foodSupply, int weaponSupply) {
    if (number < 0) throw "Cannot recruit negative soldiers";
    // cost: 1 food + 1 weapon per recruit
    int affordable = std::min(foodSupply, weaponSupply);
    int actual = (number <= affordable ? number : affordable);
    totalSoldiers_ += actual;
    // untrained count increases implicitly
    std::cout << "[Army] Recruited " << actual << " soldiers (food/weapons used).\n";
}

void Army::train(int number, int weaponSupply) {
    if (number < 0) throw "Cannot train negative soldiers";
    int untrained = totalSoldiers_ - trainedSoldiers_;
    int actual = (number <= untrained ? number : untrained);
    actual = (actual <= weaponSupply ? actual : weaponSupply);
    trainedSoldiers_ += actual;
    std::cout << "[Army] Trained " << actual << " soldiers (weapons used).\n";
}

void Army::payTroops(int goldPayment, double corruptionLevel) {
    if (goldPayment < 0) throw "Payment cannot be negative";
    // corruption steals a fraction
    double stolen = goldPayment * corruptionLevel;
    double paid = goldPayment - stolen;
    payDue_ = 0.0;
    morale_ += paid / (totalSoldiers_ + 1) * 0.01; // small boost per gold
    if (morale_ > 1.0) morale_ = 1.0;
    std::cout << "[Army] Paid troops: " << paid
        << " gold (corruption stole " << stolen << ").\n";
}

void Army::updateMorale(double corruptionLevel, double leadershipLevel) {
    // leadershipLevel in [0,1] adds, corruptionLevel in [0,1] subtracts
    morale_ += leadershipLevel * 0.05;
    morale_ -= corruptionLevel * 0.05;
    if (morale_ < 0.0) morale_ = 0.0;
    if (morale_ > 1.0) morale_ = 1.0;
    std::cout << "[Army] Morale updated to " << morale_ << "\n";
}

void Army::applyCasualties(int casualties) {
    if (casualties < 0) throw "Casualties cannot be negative";
    int loss = (casualties > totalSoldiers_ ? totalSoldiers_ : casualties);
    totalSoldiers_ -= loss;
    if (trainedSoldiers_ > totalSoldiers_) trainedSoldiers_ = totalSoldiers_;
    morale_ -= 0.1;
    if (morale_ < 0.0) morale_ = 0.0;
    std::cout << "[Army] Suffered " << loss << " casualties, morale now " << morale_ << "\n";
}

void Army::displayStatus() const {
    std::cout << "\n[Army Status]\n"
        << " Total Soldiers:   " << totalSoldiers_ << "\n"
        << " Trained Soldiers: " << trainedSoldiers_ << "\n"
        << " Morale:           " << morale_ << "\n"
        << " Pay Owed:         " << payDue_ << "\n";
}

int Army::getTotalSoldiers() const { return totalSoldiers_; }
double Army::getMorale()       const { return morale_; }
void Army::serialize(std::ostream& os) const {
    os << totalSoldiers_ << " "
        << trainedSoldiers_ << " "
        << morale_ << " "
        << payDue_ << "\n";
}
void Army::deserialize(std::istream& is) {
    is >> totalSoldiers_
        >> trainedSoldiers_
        >> morale_
        >> payDue_;
}