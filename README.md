
# 🏰 Stronghold: Medieval Kingdom Simulator

**Stronghold** is a C++ console-based simulation game where you manage a medieval kingdom, balancing population, economy, military, resources, and social class dynamics. Make strategic decisions to grow your empire and defend against internal and external threats.

## 🚀 Features

- **Social Class Simulation**: Manage Peasants, Merchants, and Nobles. Each class has unique behaviors and interactions.
- **Population Dynamics**: Simulate growth, illness, revolts, and war casualties.
- **Army Management**: Recruit, train, and maintain an army. Track morale and casualties.
- **Leadership System**: Influence kingdom stability with leader popularity and leadership skills.
- **Economy and Banking**: Tax the population, spend gold, adjust inflation, and manage loans.
- **Corruption Model**: Handle effects of corruption on all subsystems.
- **Resource Ecosystem**: Gather, consume, and trade food, wood, stone, and iron.
- **Persistent Save/Load**: Save or restore the full state of your kingdom.
- **Event System**: Random events like plagues, rebellions, and economic shifts.

## 🧱 Code Structure

- `main.cpp`: Contains the main game loop and UI.
- `Stronghold.h`: All class declarations and subsystem implementations.

### Subsystems Included:
- `SocialStructure` - Manages social classes and class interactions.
- `Population` - Handles births, deaths, illness, unrest, and revolts.
- `Army` - Recruitment, training, morale, and military stats.
- `Leader` - Manages leadership and popularity mechanics.
- `Economy` - Handles taxes, spending, inflation, and gold.
- `Bank` - Issues and tracks loans and interest.
- `Corruption` - Models effects of systemic dishonesty.
- `Resources` - Tracks resource gathering and loss.
- `EventSystem` - Random global events affecting your kingdom.

## 🛠️ Build Instructions

### Windows (Visual Studio / g++)
```bash
g++ -std=c++11 -o stronghold main.cpp
```

Make sure `Stronghold.h` is in the same directory as `main.cpp`.

### Run
```bash
./stronghold
```

## 📸 Sample Gameplay Menu

```
--- Stronghold Menu ---
1. Add Peasants
2. Add Merchants
3. Add Nobles
4. Simulate Interaction Round
...
44. Save Game
45. Load Game
46. Exit Game
```

## 💾 Save Files

- **Social Structure Save**: `social_save.txt`
- **Entire Game Save**: `game_save.txt`

## 🎮 Controls

Use numeric keys to navigate menus. Game supports input via standard console.

## 📋 To Do / Ideas

- Add diplomacy or war with neighboring kingdoms.
- Expand AI-driven dynamic events.
- Include graphical interface using SDL or Qt.
- Add achievements and win/loss conditions.

## 📜 License

This project is released under the MIT License.

---

**Enjoy building and ruling your stronghold!**
