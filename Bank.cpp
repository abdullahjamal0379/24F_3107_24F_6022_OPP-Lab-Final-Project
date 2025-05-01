#include "Stronghold.h"
#include <iostream>
#include <cstdlib>

Bank::Bank(int loan, double interest)
    : loanAmount_(loan), interestRate_(interest) {
}

void Bank::issueLoan(int amount, Economy& economy) {
    loanAmount_ += amount;
    economy.addGold(amount);
    std::cout << "[Bank] Issued loan of " << amount << " gold.\n";
}

void Bank::repayLoan(int amount, Economy& economy) {
    if (amount > economy.getGold()) {
        std::cout << "[Bank] Not enough gold in treasury to repay.\n";
        return;
    }
    int repayment = std::min(amount, loanAmount_);
    economy.spendGold(repayment);
    loanAmount_ -= repayment;
    std::cout << "[Bank] Repaid " << repayment << " of loan.\n";
}

void Bank::adjustInterestRate(double rate) {
    if (rate < 0.0) rate = 0.0;
    if (rate > 1.0) rate = 1.0;
    interestRate_ = rate;
    std::cout << "[Bank] Interest rate set to " << interestRate_ * 100 << "%\n";
}

void Bank::detectFraud(double corruptionLevel, Economy& economy) {
    int fraudChance = int(corruptionLevel * 100);
    int roll = rand() % 100;
    if (roll < fraudChance) {
        int stolen = economy.getGold() * 0.10;
        economy.spendGold(stolen);
        std::cout << "[Bank] Fraud detected! " << stolen << " gold embezzled.\n";
    }
    else {
        std::cout << "[Bank] No fraud detected in audit.\n";
    }
}

void Bank::displayStatus() const {
    std::cout << "\n[Bank Status]\n"
        << " Loan Outstanding: " << loanAmount_ << "\n"
        << " Interest Rate: " << interestRate_ * 100 << "%\n";
}

void Bank::serialize(std::ostream& os) const {
    os << loanAmount_ << " " << interestRate_ << "\n";
}

void Bank::deserialize(std::istream& is) {
    is >> loanAmount_ >> interestRate_;
}
