#include "Stronghold.h"
#include <iostream>

Economy::Economy(int gold, double inflation, int tax)
    : gold_(gold), inflationRate_(inflation), taxRate_(tax) {
}

void Economy::collectTaxes(int population) {
    int collected = (population * taxRate_) / 100;
    gold_ += collected;
    std::cout << "[Economy] Collected " << collected << " gold from taxes.\n";
}

void Economy::applyInflation() {
    int loss = gold_ * inflationRate_;
    gold_ -= loss;
    std::cout << "[Economy] Inflation reduced treasury by " << loss << " gold.\n";
}

void Economy::spendGold(int amount) {
    if (amount > gold_) amount = gold_;
    gold_ -= amount;
    std::cout << "[Economy] Spent " << amount << " gold.\n";
}

void Economy::addGold(int amount) {
    gold_ += amount;
    std::cout << "[Economy] Added " << amount << " gold.\n";
}

void Economy::adjustTaxRate(int rate) {
    if (rate < 0) rate = 0;
    if (rate > 100) rate = 100;
    taxRate_ = rate;
    std::cout << "[Economy] Tax rate adjusted to " << taxRate_ << "%\n";
}

void Economy::displayStatus() const {
    std::cout << "\n[Economy Status]\n"
        << " Gold: " << gold_ << "\n"
        << " Inflation: " << inflationRate_ << "\n"
        << " Tax Rate: " << taxRate_ << "%\n";
}

void Economy::serialize(std::ostream& os) const {
    os << gold_ << " " << inflationRate_ << " " << taxRate_ << "\n";
}

void Economy::deserialize(std::istream& is) {
    is >> gold_ >> inflationRate_ >> taxRate_;
}

int Economy::getGold() const { return gold_; }
double Economy::getInflation() const { return inflationRate_; }
int Economy::getTaxRate() const { return taxRate_; }
