// main.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <fstream>
#include "Stronghold.h"

using namespace std;

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    // Subsystems
    SocialStructure social;
    Population         pop(1000, 800, 1200);
    Army               army(0);
    Leader leader("King Aric");
    Economy economy(1000, 0.05, 10);
    Bank bank;
    Corruption corruption;
    Resources resources(100, 100, 100, 100);
    int choice = 0;
    // Initial demo setup for SocialStructure
    cout << "Welcome to Strong Hold! Defeat your enemy.." << endl;
    system("pause");
    system("cls");
    try {
        social.addClass(new Peasant(1000, 0.50));
        social.addClass(new Merchant(200, 0.70, 500.0));
        social.addClass(new Noble(50, 0.90, 100.0));
    }
    catch (const char* e) {
        cerr << "Init error: " << e << endl;
        return EXIT_FAILURE;
    }

    do {
        cout << "\n--- Stronghold Menu ---\n";
        cout << "1.  Add Peasants\n";
        cout << "2.  Add Merchants\n";
        cout << "3.  Add Nobles\n";
        cout << "4.  Simulate Interaction Round\n";
        cout << "5.  Show Social Status\n";
        cout << "6.  Save Social Structure\n";
        cout << "7.  Load Social Structure\n";
        cout << "\n-- Population Dynamics --\n";
        cout << "8.  Add Births\n";
        cout << "9.  Add Deaths\n";
        cout << "10. Simulate Illness\n";
        cout << "11. Update Unrest\n";
        cout << "12. Simulate Revolt\n";
        cout << "13. Apply War Casualties (Population)\n";
        cout << "\n-- Military System --\n";
        cout << "14. Recruit Soldiers\n";
        cout << "15. Train Soldiers\n";
        cout << "16. Pay Troops\n";
        cout << "17. Update Army Morale\n";
        cout << "18. Show Army Status\n";
        cout << "\n-- Leadership --\n";
        cout << "19. Show Leader Status\n";
        cout << "20. Improve Leadership\n";
        cout << "21. Change Popularity\n";
        cout << "22. Simulate Coup\n";
        cout << "23. Elect New Leader\n";
        cout << "\n-- Economic Management --\n";
        cout << "24. Show Economy Status\n";
        cout << "25. Collect Taxes\n";
        cout << "26. Apply Inflation\n";
        cout << "27. Spend Gold\n";
        cout << "28. Add Gold\n";
        cout << "29. Adjust Tax Rate\n";
        cout << "\n-- Banking & Corruption --\n";
        cout << "30. Issue Loan\n";
        cout << "31. Repay Loan\n";
        cout << "32. Adjust Interest Rate\n";
        cout << "33. Detect Fraud (Audit)\n";
        cout << "34. Show Bank Status\n";
        cout << "35. Show Corruption Level\n";
        cout << "36. Increase Corruption\n";
        cout << "37. Decrease Corruption\n";
        cout << "\n-- Resource Ecosystem --\n";
        cout << "38. Show Resources\n";
        cout << "39. Gather Resources\n";
        cout << "40. Consume Resources\n";
        cout << "41. Trade Resources\n";
        cout << "42. Simulate Resource Loss\n";
        cout << "\n43. Show All Status\n";
        cout << "44. Save Game\n";
        cout << "45. Load Game\n";
        cout << "46. Exit Game\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            // ── SocialStructure ─────────────────────────────────────────────────
        case 1: {
            int cnt; cout << "Number of peasants to add: "; cin >> cnt;
            social.addClass(new Peasant(cnt, 0.50));
            cout << "Added " << cnt << " peasants.\n";
            social.displayStatus();
            break;
        }
        case 2: {
            int cnt; cout << "Number of merchants to add: "; cin >> cnt;
            social.addClass(new Merchant(cnt, 0.70, 100.0 * cnt));
            cout << "Added " << cnt << " merchants.\n";
            social.displayStatus();
            break;
        }
        case 3: {
            int cnt; cout << "Number of nobles to add: "; cin >> cnt;
            social.addClass(new Noble(cnt, 0.90, 10.0 * cnt));
            cout << "Added " << cnt << " nobles.\n";
            social.displayStatus();
            break;
        }
        case 4:
            social.simulateInteraction();
            cout << "-> Interaction simulated.\n";
            social.displayStatus();
            break;
        case 5:
            social.displayStatus();
            break;
        case 6: {
            cout << "\n-- Before Saving --\n"; social.displayStatus();
            cout << "Save this state? (Y/N): ";
            char c; cin >> c;
            if (c == 'Y' || c == 'y') {
                ofstream ofs("social_save.txt");
                if (!ofs) cerr << "Save error\n";
                else { social.serialize(ofs); cout << "Saved.\n"; }
            }
            break;
        }
        case 7: {
            cout << "\n-- Before Loading --\n"; social.displayStatus();
            cout << "Load state? (Y/N): ";
            char c; cin >> c;
            if (c == 'Y' || c == 'y') {
                ifstream ifs("social_save.txt");
                if (!ifs) cerr << "Load error\n";
                else {
                    social.clear(); social.deserialize(ifs);
                    cout << "\n-- After Loading --\n";
                    social.displayStatus();
                }
            }
            break;
        }

              // ── Population ────────────────────────────────────────────────────────
        case 8: {
            int b, f; cout << "Births: "; cin >> b;
            cout << "Food supply: "; cin >> f;
            pop.grow(b, f);
            pop.displayStatus();
            break;
        }
        case 9: {
            int d; cout << "Deaths: "; cin >> d;
            pop.die(d);
            pop.displayStatus();
            break;
        }
        case 10:
            pop.simulateIllness();
            pop.displayStatus();
            break;
        case 11: {
            int f; cout << "Food supply: "; cin >> f;
            pop.updateUnrest(f);
            pop.displayStatus();
            break;
        }
        case 12: {
            int f; cout << "Food supply: "; cin >> f;
            pop.simulateRevolt(f);
            pop.displayStatus();
            break;
        }
        case 13: {
            int c; cout << "War casualties: "; cin >> c;
            pop.applyWar(c);
            pop.displayStatus();
            break;
        }

               // ── Army ─────────────────────────────────────────────────────────────
        case 14: {
            int num, food, weapons;
            cout << "Recruits: ";    cin >> num;
            cout << "Food supply: "; cin >> food;
            cout << "Weapons: ";     cin >> weapons;
            army.recruit(num, food, weapons);
            break;
        }
        case 15: {
            int num, weapons;
            cout << "Train count: "; cin >> num;
            cout << "Weapons: ";     cin >> weapons;
            army.train(num, weapons);
            break;
        }
        case 16: {
            int gold; double corrupt;
            cout << "Gold payment: ";        cin >> gold;
            cout << "Corruption lvl (0–1): "; cin >> corrupt;
            army.payTroops(gold, corrupt);
            break;
        }
        case 17: {
            double corrupt, leader;
            cout << "Corruption lvl (0–1): ";   cin >> corrupt;
            cout << "Leadership lvl (0–1): ";    cin >> leader;
            army.updateMorale(corrupt, leader);
            break;
        }
        case 18:
            army.displayStatus();
            break;
        case 19:
            leader.displayStatus();
            break;
        case 20: {
            double amt;
            cout << "Amount to improve (0-1): "; cin >> amt;
            leader.improveLeadership(amt);
            break;
        }
        case 21: {
            double amt;
            cout << "Popularity change (-1 to 1): "; cin >> amt;
            leader.changePopularity(amt);
            break;
        }
        case 22:
            leader.simulateCoup();
            break;
        case 23: {
            string newName;
            cout << "New leader name: ";
            cin.ignore();
            getline(cin, newName);
            leader.electNewLeader(newName);
            break;
        }
        case 24:
            economy.displayStatus();
            break;
        case 25:
            economy.collectTaxes(pop.getTotalPopulation());
            break;
        case 26:
            economy.applyInflation();
            break;
        case 27: {
            int amt;
            cout << "Spend how much gold? ";
            cin >> amt;
            economy.spendGold(amt);
            break;
        }
        case 28: {
            int amt;
            cout << "Add how much gold? ";
            cin >> amt;
            economy.addGold(amt);
            break;
        }
        case 29: {
            int rate;
            cout << "New tax rate (0–100): ";
            cin >> rate;
            economy.adjustTaxRate(rate);
            break;
        }
        case 30: {
            int amt;
            cout << "Loan amount: "; cin >> amt;
            bank.issueLoan(amt, economy);
            break;
        }
        case 31: {
            int amt;
            cout << "Repayment amount: "; cin >> amt;
            bank.repayLoan(amt, economy);
            break;
        }
        case 32: {
            double rate;
            cout << "New interest rate (0.0–1.0): "; cin >> rate;
            bank.adjustInterestRate(rate);
            break;
        }
        case 33:
            bank.detectFraud(corruption.getLevel(), economy);
            break;
        case 34:
            bank.displayStatus();
            break;
        case 35:
            corruption.displayStatus();
            break;
        case 36: {
            double amt;
            cout << "Increase corruption by (0–1): "; cin >> amt;
            corruption.increase(amt);
            break;
        }
        case 37: {
            double amt;
            cout << "Decrease corruption by (0–1): "; cin >> amt;
            corruption.decrease(amt);
            break;
        }
        case 38:
            resources.displayStatus();
            break;
        case 39: {
            int f, w, s, i;
            cout << "Gather - Food: "; cin >> f;
            cout << "         Wood: "; cin >> w;
            cout << "         Stone: "; cin >> s;
            cout << "         Iron: "; cin >> i;
            resources.gather(f, w, s, i);
            break;
        }
        case 40: {
            int f, w, s, i;
            cout << "Consume - Food: "; cin >> f;
            cout << "           Wood: "; cin >> w;
            cout << "           Stone: "; cin >> s;
            cout << "           Iron: "; cin >> i;
            resources.consume(f, w, s, i);
            break;
        }
        case 41: {
            int f, w, s, i;
            cout << "Trade for - Food: "; cin >> f;
            cout << "             Wood: "; cin >> w;
            cout << "             Stone: "; cin >> s;
            cout << "             Iron: "; cin >> i;
            resources.trade(economy.getGold(), f, w, s, i, economy);
            break;
        }
        case 42:
            resources.simulateLoss();
            break;
        case 43:
            // display social, population, and army all at once
            cout << "\n=== Full State ===\n";
            social.displayStatus();
            pop.displayStatus();
            army.displayStatus();
            leader.displayStatus();
            economy.displayStatus();
            bank.displayStatus();
            corruption.displayStatus();
            resources.displayStatus();

            break;

        case 44: {
            cout << "Save entire game to file? (Y/N): ";
            char c; cin >> c;
            if (c == 'Y' || c == 'y') {
                ofstream ofs("game_save.txt");
                if (!ofs) {
                    cerr << "Could not open save file!\n";
                }
                else {
                    // first social
                    social.serialize(ofs);
                    // marker so we know where each section begins
                    ofs << "#POP\n";
                    pop.serialize(ofs);
                    ofs << "#ARMY\n";
                    army.serialize(ofs);
                    ofs << "#LEADER\n";
                    leader.serialize(ofs);
                    ofs << "#ECONOMY\n";
                    economy.serialize(ofs);
                    ofs << "#BANK\n";
                    bank.serialize(ofs);
                    ofs << "#CORRUPTION\n";
                    corruption.serialize(ofs);
                    ofs << "#RESOURCES\n";
                    resources.serialize(ofs);

                    ofs.close();
                    cout << "Game saved.\n";
                }
            }
            break;
        }

        case 45: {
            cout << "Load entire game from file? (Y/N): ";
            char c; cin >> c;
            if (c == 'Y' || c == 'y') {
                ifstream ifs("game_save.txt");
                if (!ifs) {
                    cerr << "Could not open save file!\n";
                }
                else {
                    // social
                    social.clear();
                    social.deserialize(ifs);
                    // skip marker
                    string marker;
                    ifs >> marker;  // reads "#POP"
                    pop.deserialize(ifs);
                    ifs >> marker;  // reads "#ARMY"
                    army.deserialize(ifs);
                    ifs >> marker;  // should read #LEADER
                    leader.deserialize(ifs);
                    ifs >> marker; // reads #ECONOMY
                    economy.deserialize(ifs);
                    ifs >> marker; // reads #BANK
                    bank.deserialize(ifs);
                    ifs >> marker; // reads #CORRUPTION
                    corruption.deserialize(ifs);
                    ifs >> marker; // #RESOURCES
                    resources.deserialize(ifs);

                    ifs.close();
                    cout << "Game loaded.\n";
                }
            }
            break;
        }

        case 46:
            cout << "Exiting game. Farewell!\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
        if (true) { // 30% chance per turn
            EventSystem::triggerRandomEvent(pop, army, resources, economy, leader, corruption);
        }
        cout << "Press any key to continue...";
        _getch();
        system("cls");
    } while (choice != 46);

    return 0;
}
