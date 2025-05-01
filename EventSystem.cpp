#include "Stronghold.h"
#include <iostream>
#include <cstdlib>

void EventSystem::triggerRandomEvent(Population& pop, Army& army, Resources& res,
    Economy& eco, Leader& leader, Corruption& corruption) {
    int event = rand() % 6;

    switch (event) {
    case 0: // ⚔️ War breaks out
        std::cout << "\n⚔️ WAR EVENT! Army suffers casualties.\n";
        pop.applyWar(50);
        army.applyCasualties(30);
        eco.applyInflation();
        leader.changePopularity(-0.2);
        break;

    case 1: // 🌾 Famine
        std::cout << "\n🌾 FAMINE EVENT! Food shortage hits population.\n";
        res.consume(50, 0, 0, 0);
        pop.updateUnrest(res.getFood());
        pop.simulateRevolt(res.getFood());
        leader.changePopularity(-0.1);
        break;

    case 2: // ☣️ Plague
        std::cout << "\n☣️ PLAGUE EVENT! People fall ill.\n";
        pop.simulateIllness();
        pop.die(30);
        leader.changePopularity(-0.1);
        break;

    case 3: // 💸 Embezzlement
        std::cout << "\n💸 FRAUD EVENT! Corruption triggers gold theft.\n";
        corruption.increase(0.1);
        eco.spendGold(eco.getGold() * 0.1);
        break;

    case 4: // 🌪️ Storm damages resources
        std::cout << "\n🌪️ STORM EVENT! Natural disaster destroys resources.\n";
        res.simulateLoss();
        break;

    case 5: // 🪓 Betrayal
        std::cout << "\n🪓 BETRAYAL EVENT! A leader loses favor.\n";
        leader.simulateCoup();
        leader.changePopularity(-0.2);
        corruption.increase(0.1);
        break;
    }
}
