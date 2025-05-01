#include "Stronghold.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// ─── Population definitions ─────────────────────────────────────────────────

Population::Population(int initial, int employed, int shelter)
    : totalPeople_(initial), unrest_(0.0),
    employed_(employed), shelterCapacity_(shelter)
{
    if (initial < 0 || employed < 0 || shelter<0 || employed>initial || shelter < initial)
        throw "Invalid Population parameters";
}

void Population::setEmployment(int e) {
    if (e<0 || e>totalPeople_) throw "Employment out of range";
    employed_ = e;
}

void Population::setShelterCapacity(int c) {
    if (c < 0) throw "Shelter capacity cannot be negative";
    shelterCapacity_ = c;
}

void Population::grow(int births, int food) {
    if (births < 0) throw "Births cannot be negative";
    int actual = (food >= births ? births : births / 2);
    if (actual + totalPeople_ > shelterCapacity_) actual = shelterCapacity_ - totalPeople_;
    if (actual > employed_) actual = employed_;
    totalPeople_ += (actual > 0 ? actual : 0);
    std::cout << "[Grow] +" << actual << " people\n";
}

void Population::die(int deaths) {
    if (deaths < 0) throw "Deaths cannot be negative";
    int actual = (deaths > totalPeople_ ? totalPeople_ : deaths);
    totalPeople_ -= actual;
    std::cout << "[Death] -" << actual << " people\n";
}

void Population::applyWar(int c) {
    if (c < 0) throw "Casualties cannot be negative";
    int loss = (c > totalPeople_ ? totalPeople_ : c);
    totalPeople_ -= loss;
    unrest_ += 0.1; if (unrest_ > 1.0) unrest_ = 1.0;
    std::cout << "[War] -" << loss << " people, unrest up\n";
}

void Population::simulateIllness() {
    int deaths = int(totalPeople_ * (std::rand() % 6) / 100.0);
    totalPeople_ -= deaths;
    if (deaths > 0) std::cout << "[Disease] -" << deaths << " people\n";
}

void Population::updateUnrest(int food) {
    if (food < totalPeople_) unrest_ += 0.1;
    double unempRate = 1.0 - double(employed_) / totalPeople_;
    unrest_ += 0.1 * unempRate;
    if (unrest_ < 0.0) unrest_ = 0.0;
    if (unrest_ > 1.0) unrest_ = 1.0;
    std::cout << "[Unrest] now " << unrest_ << "\n";
}

void Population::simulateRevolt(int food) {
    if (unrest_ > 0.8 && food < totalPeople_) {
        int loss = int(totalPeople_ * 0.1);
        totalPeople_ -= loss;
        unrest_ = 0.5;
        std::cout << "[Revolt] -" << loss << " people, unrest=0.5\n";
    }
}

void Population::displayStatus() const {
    std::cout << "\n[Population]\n"
        << " Total:     " << totalPeople_ << "\n"
        << " Employed:  " << employed_ << "\n"
        << " Shelter:   " << shelterCapacity_ << "\n"
        << " Unrest:    " << unrest_ << "\n";
}

int Population::getTotalPopulation() const { return totalPeople_; }
double Population::getUnrest()        const { return unrest_; }
int Population::getEmployed()        const { return employed_; }
int Population::getShelterCapacity() const { return shelterCapacity_; }
void Population::serialize(std::ostream& os) const {
    os << totalPeople_ << " "
        << employed_ << " "
        << shelterCapacity_ << " "
        << unrest_ << "\n";
}

void Population::deserialize(std::istream& is) {
    is >> totalPeople_
        >> employed_
        >> shelterCapacity_
        >> unrest_;
}
