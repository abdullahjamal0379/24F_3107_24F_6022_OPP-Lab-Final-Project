#include "Stronghold.h"
#include <iostream>

Corruption::Corruption(double level) : level_(level) {}

void Corruption::increase(double amount) {
    level_ += amount;
    if (level_ > 1.0) level_ = 1.0;
    std::cout << "[Corruption] Level increased to " << level_ << "\n";
}

void Corruption::decrease(double amount) {
    level_ -= amount;
    if (level_ < 0.0) level_ = 0.0;
    std::cout << "[Corruption] Level decreased to " << level_ << "\n";
}

double Corruption::getLevel() const {
    return level_;
}

void Corruption::displayStatus() const {
    std::cout << "\n[Corruption Status]\n"
        << " Level: " << level_ << "\n";
}

void Corruption::serialize(std::ostream& os) const {
    os << level_ << "\n";
}

void Corruption::deserialize(std::istream& is) {
    is >> level_;
}
