#ifndef STRONGHOLD_H
#define STRONGHOLD_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <conio.h>

// Base class for any social class in the kingdom
class SocialClass {
protected:
    std::string name_;
    int population_;
    double loyalty_;    // 0.0 (rebellious) to 1.0 (totally loyal)

public:
    SocialClass(const std::string& name, int population, double loyalty);
    virtual ~SocialClass();

    // Defines how this class interacts with another
    virtual void interact(SocialClass* other) = 0;

    // Getters & setters
    const std::string& getName() const;
    int getPopulation() const;
    double getLoyalty() const;
    void setPopulation(int pop);
    void setLoyalty(double loyalty);
};

// Peasant class
class Peasant : public SocialClass {
public:
    Peasant(int population, double loyalty);
    void interact(SocialClass* other) override;
};

// Merchant class
class Merchant : public SocialClass {
    double wealth_;

public:
    Merchant(int population, double loyalty, double wealth);
    void interact(SocialClass* other) override;

    double getWealth() const;
    void setWealth(double w);
};

// Noble class
class Noble : public SocialClass {
    double influence_;

public:
    Noble(int population, double loyalty, double influence);
    void interact(SocialClass* other) override;

    double getInfluence() const;
    void setInfluence(double inf);
};

// Manager class for all social classes
class SocialStructure {
    SocialClass** classes_;   // dynamic array of pointers
    int count_;

public:
    SocialStructure();
    ~SocialStructure();

    // add one SocialClass (Peasant*, Merchant*, Noble*) to the system
    void addClass(SocialClass* sc);

    // run a pass of interactions among all classes
    void simulateInteraction();

    // display each class’s current status
    void displayStatus() const;

    // remove all entries
    void clear();

    // save to stream
    void serialize(std::ostream& os) const;

    // load from stream
    void deserialize(std::istream& is);
};
// ─── Population subsystem ─────────────────────────────────────────────────
class Population {
private:
    int totalPeople_;       // current population
    double unrest_;         // 0.0 (peace) to 1.0 (full revolt)
    int employed_;          // number currently employed
    int shelterCapacity_;   // how many people can be housed

public:
    Population(int initial = 0, int employed = 0, int shelter = 0);

    void setEmployment(int employed);
    void setShelterCapacity(int capacity);

    void grow(int births, int foodSupply);
    void die(int deaths);
    void applyWar(int casualties);
    void simulateIllness();

    void updateUnrest(int foodSupply);
    void simulateRevolt(int foodSupply);

    void displayStatus() const;
    int  getTotalPopulation() const;
    double getUnrest() const;
    int  getEmployed() const;
    int  getShelterCapacity() const;
    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);
};
// ─── Army subsystem ─────────────────────────────────────────────────────────
class Army {
private:
    int totalSoldiers_;    // how many in the army
    int trainedSoldiers_;  // of those, how many are trained
    double morale_;        // 0.0 (mutinous) to 1.0 (steadfast)
    double payDue_;        // gold owed but not yet paid

public:
    // ctor: optional starting force
    Army(int initial);

    // recruit consumes food and weapons, adds new untrained soldiers
    void recruit(int number, int foodSupply, int weaponSupply);

    // train consumes weapons (or time) and moves untrained → trained
    void train(int number, int weaponSupply);

    // pay troops: you give goldPayment, corruption eats into it
    void payTroops(int goldPayment, double corruptionLevel);

    // morale depends on corruption (–) and leadership (+)
    void updateMorale(double corruptionLevel, double leadershipLevel);

    // apply casualties from battle
    void applyCasualties(int casualties);

    // report current army stats
    void displayStatus() const;

    // getters for other subsystems
    int getTotalSoldiers() const;
    double getMorale() const;
    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);
};
// ─── Leadership subsystem ─────────────────────────────────────────────────────
class Leader {
private:
    std::string name_;
    double popularity_;     // 0.0 to 1.0
    double leadershipLevel_; // 0.0 to 1.0
    bool isAlive_;

public:
    Leader(const std::string& name = "Unknown", double popularity = 0.5, double level = 0.5);

    void improveLeadership(double amount);
    void changePopularity(double delta);
    void kill();  // Used during coups or war
    void electNewLeader(const std::string& newName);
    void simulateCoup();  // Random chance to lose leadership

    void displayStatus() const;

    // Save/load
    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);

    // Getters for other systems
    double getPopularity() const;
    double getLeadershipLevel() const;
    bool isLeaderAlive() const;
};
// ─── Economy subsystem ──────────────────────────────────────────────────────
class Economy {
private:
    int gold_;             // treasury
    double inflationRate_; // 0.0 to 1.0
    int taxRate_;          // 0 to 100 (percentage)

public:
    Economy(int gold = 1000, double inflation = 0.05, int tax = 10);

    void collectTaxes(int population);
    void applyInflation();
    void spendGold(int amount);
    void addGold(int amount);
    void adjustTaxRate(int rate);

    void displayStatus() const;

    // Save/load
    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);

    int getGold() const;
    double getInflation() const;
    int getTaxRate() const;
};
// ─── Banking subsystem ───────────────────────────────────────────────────────
class Bank {
private:
    int loanAmount_;
    double interestRate_;  // e.g., 0.05 means 5%

public:
    Bank(int loan = 0, double interest = 0.05);

    void issueLoan(int amount, Economy& economy);
    void repayLoan(int amount, Economy& economy);
    void adjustInterestRate(double rate);
    void detectFraud(double corruptionLevel, Economy& economy);

    void displayStatus() const;

    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);
};
// ─── Corruption subsystem ────────────────────────────────────────────────────
class Corruption {
private:
    double level_; // 0.0 = honest, 1.0 = totally corrupt

public:
    Corruption(double level = 0.2);

    void increase(double amount);
    void decrease(double amount);
    double getLevel() const;

    void displayStatus() const;

    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);
};
// ─── Resource subsystem ──────────────────────────────────────────────────────
class Resources {
private:
    int food_;
    int wood_;
    int stone_;
    int iron_;

public:
    Resources(int f = 100, int w = 100, int s = 100, int i = 100);

    void gather(int f, int w, int s, int i);
    void consume(int f, int w, int s, int i);
    void trade(int gold, int f, int w, int s, int i, Economy& economy);
    void simulateLoss();  // random loss event

    void displayStatus() const;

    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);

    // Getters
    int getFood() const;
    int getWood() const;
    int getStone() const;
    int getIron() const;
};
// ─── Event System ─────────────────────────────────────────────────────────────
class EventSystem {
public:
    static void triggerRandomEvent(Population& pop, Army& army, Resources& res,
        Economy& eco, Leader& leader, Corruption& corruption);
};

#endif // STRONGHOLD_H
