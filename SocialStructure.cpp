#include "Stronghold.h"
#include <iostream>
#include <string>

// ------- SocialClass definitions --------

SocialClass::SocialClass(const std::string& name, int population, double loyalty)
    : name_(name), population_(population), loyalty_(loyalty)
{
    if (population < 0 || loyalty < 0.0 || loyalty > 1.0)
        throw "Invalid SocialClass parameters";
}

SocialClass::~SocialClass() {}

const std::string& SocialClass::getName() const { return name_; }
int SocialClass::getPopulation() const { return population_; }
double SocialClass::getLoyalty() const { return loyalty_; }

void SocialClass::setPopulation(int pop) {
    if (pop < 0) throw "Population cannot be negative";
    population_ = pop;
}

void SocialClass::setLoyalty(double loyalty) {
    if (loyalty < 0.0 || loyalty > 1.0)
        throw "Loyalty must be in [0.0,1.0]";
    loyalty_ = loyalty;
}

// ------- Peasant --------

Peasant::Peasant(int population, double loyalty)
    : SocialClass("Peasant", population, loyalty)
{
}

void Peasant::interact(SocialClass* other) {
    if (other->getName() == "Noble") {
        double updated = loyalty_ + 0.05;
        loyalty_ = (updated > 1.0 ? 1.0 : updated);
    }
    else {
        double updated = loyalty_ - 0.02;
        loyalty_ = (updated < 0.0 ? 0.0 : updated);
    }
}

// ------- Merchant --------

Merchant::Merchant(int population, double loyalty, double wealth)
    : SocialClass("Merchant", population, loyalty), wealth_(wealth)
{
    if (wealth < 0.0) throw "Wealth cannot be negative";
}

void Merchant::interact(SocialClass* other) {
    if (other->getName() == "Peasant") {
        wealth_ += 10.0;
        double updated = loyalty_ - 0.01;
        loyalty_ = (updated < 0.0 ? 0.0 : updated);
    }
}

double Merchant::getWealth() const { return wealth_; }
void Merchant::setWealth(double w) {
    if (w < 0.0) throw "Wealth cannot be negative";
    wealth_ = w;
}

// ------- Noble --------

Noble::Noble(int population, double loyalty, double influence)
    : SocialClass("Noble", population, loyalty), influence_(influence)
{
    if (influence < 0.0) throw "Influence cannot be negative";
}

void Noble::interact(SocialClass* other) {
    if (other->getName() == "Peasant") {
        influence_ *= 0.99;
    }
    double updated = loyalty_ + 0.02;
    loyalty_ = (updated > 1.0 ? 1.0 : updated);
}

double Noble::getInfluence() const { return influence_; }
void Noble::setInfluence(double inf) {
    if (inf < 0.0) throw "Influence cannot be negative";
    influence_ = inf;
}

// ------- SocialStructure --------

SocialStructure::SocialStructure()
    : classes_(nullptr), count_(0)
{
}

SocialStructure::~SocialStructure() {
    clear();
}

void SocialStructure::addClass(SocialClass* sc) {
    SocialClass** temp = new SocialClass * [count_ + 1];
    for (int i = 0; i < count_; ++i)
        temp[i] = classes_[i];
    temp[count_] = sc;
    delete[] classes_;
    classes_ = temp;
    ++count_;
}

void SocialStructure::simulateInteraction() {
    for (int i = 0; i < count_; ++i) {
        for (int j = 0; j < count_; ++j) {
            if (i != j)
                classes_[i]->interact(classes_[j]);
        }
    }
}

void SocialStructure::displayStatus() const {
    std::cout << "\n--- Social Structure Status ---\n";
    for (int i = 0; i < count_; ++i) {
        SocialClass* sc = classes_[i];
        std::cout << sc->getName()
            << " | Pop=" << sc->getPopulation()
            << " | Loyalty=" << sc->getLoyalty();

        if (sc->getName() == "Merchant") {
            Merchant* m = static_cast<Merchant*>(sc);
            std::cout << " | Wealth=" << m->getWealth();
        }
        else if (sc->getName() == "Noble") {
            Noble* n = static_cast<Noble*>(sc);
            std::cout << " | Influence=" << n->getInfluence();
        }

        std::cout << "\n";
    }
}

void SocialStructure::clear() {
    for (int i = 0; i < count_; ++i)
        delete classes_[i];
    delete[] classes_;
    classes_ = nullptr;
    count_ = 0;
}

void SocialStructure::serialize(std::ostream& os) const {
    os << count_ << "\n";
    for (int i = 0; i < count_; ++i) {
        SocialClass* sc = classes_[i];
        os << sc->getName() << " "
            << sc->getPopulation() << " "
            << sc->getLoyalty();
        if (sc->getName() == "Merchant") {
            Merchant* m = static_cast<Merchant*>(sc);
            os << " " << m->getWealth();
        }
        else if (sc->getName() == "Noble") {
            Noble* n = static_cast<Noble*>(sc);
            os << " " << n->getInfluence();
        }
        os << "\n";
    }
}

void SocialStructure::deserialize(std::istream& is) {
    int n;
    if (!(is >> n)) return;

    clear();
    for (int i = 0; i < n; ++i) {
        std::string type;
        int pop;
        double loyalty;
        is >> type >> pop >> loyalty;

        if (type == "Peasant") {
            addClass(new Peasant(pop, loyalty));
        }
        else if (type == "Merchant") {
            double wealth;
            is >> wealth;
            addClass(new Merchant(pop, loyalty, wealth));
        }
        else if (type == "Noble") {
            double influence;
            is >> influence;
            addClass(new Noble(pop, loyalty, influence));
        }
    }
}
