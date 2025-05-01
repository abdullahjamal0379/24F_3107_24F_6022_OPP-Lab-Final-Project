#include "Stronghold.h"
#include <iostream>
#include <cstdlib>

Resources::Resources(int f, int w, int s, int i)
    : food_(f), wood_(w), stone_(s), iron_(i) {
}

void Resources::gather(int f, int w, int s, int i) {
    food_ += f; wood_ += w; stone_ += s; iron_ += i;
    std::cout << "[Resources] Gathered - Food: " << f
        << ", Wood: " << w << ", Stone: " << s << ", Iron: " << i << "\n";
}

void Resources::consume(int f, int w, int s, int i) {
    food_ = std::max(0, food_ - f);
    wood_ = std::max(0, wood_ - w);
    stone_ = std::max(0, stone_ - s);
    iron_ = std::max(0, iron_ - i);
    std::cout << "[Resources] Consumed - Food: " << f
        << ", Wood: " << w << ", Stone: " << s << ", Iron: " << i << "\n";
}

void Resources::trade(int gold, int f, int w, int s, int i, Economy& economy) {
    int total = f + w + s + i;
    int cost = total * 10; // each unit = 10 gold
    if (cost > economy.getGold()) {
        std::cout << "[Trade] Not enough gold to trade.\n";
        return;
    }
    economy.spendGold(cost);
    gather(f, w, s, i);
    std::cout << "[Trade] Traded " << cost << " gold for resources.\n";
}

void Resources::simulateLoss() {
    int lossF = rand() % 10;
    int lossW = rand() % 5;
    int lossS = rand() % 5;
    int lossI = rand() % 3;
    consume(lossF, lossW, lossS, lossI);
    std::cout << "[Resources] Random loss occurred due to spoilage or theft.\n";
}

void Resources::displayStatus() const {
    std::cout << "\n[Resource Status]\n"
        << " Food:  " << food_ << "\n"
        << " Wood:  " << wood_ << "\n"
        << " Stone: " << stone_ << "\n"
        << " Iron:  " << iron_ << "\n";
}

void Resources::serialize(std::ostream& os) const {
    os << food_ << " " << wood_ << " " << stone_ << " " << iron_ << "\n";
}

void Resources::deserialize(std::istream& is) {
    is >> food_ >> wood_ >> stone_ >> iron_;
}

int Resources::getFood() const { return food_; }
int Resources::getWood() const { return wood_; }
int Resources::getStone() const { return stone_; }
int Resources::getIron() const { return iron_; }
