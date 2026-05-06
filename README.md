# Hunter RPG (v6.0 Update)

Hunter RPG is a text-based C++ Role-Playing Game (MUD style) where you step into the shoes of a newly awakened Hunter.

Explore different gates, battle procedurally generated monsters, and survive as long as you can!

## Features

*   **FSM-based Game Engine:** The core game loop has been refactored to use a Finite State Machine (FSM) architecture.
*   **ANSI Fixed-Frame UI & Scrolling Event Log:** The battle UI now utilizes standard C++ ANSI escape codes to present a clean, fixed-frame interface featuring a 10-line scrolling message log, rather than simply clearing and rewriting the screen manually.
*   **Skill Mastery System (+10% per level):** Combat skills now level up upon repeated use (`uses >= level * 5`), permanently augmenting their power by +10% per skill level! Basic attacks remain unchanged.
*   **Stat-Scaling Signature Skills:** Elite monsters and player classes now use dynamically stat-scaling unique skills (`HeavyStrike`, `Snipe`, `MagicExplosion`, `ShieldBash`, `DivineGrace`) rather than generic damage!
*   **Random Event Engine (Post-Gate Events):** Post-gate events that can boost your luck dynamically.
*   **Structured LUCK Stat:** Luck is structured dynamically into characters.
*   **Item Rarity System (Normal/Magic/Rare):** Drops categorized dynamically by their rarity value based on luck and elite biases.
*   **Elite Monster UI Visibility:** Identify Elite Monsters directly on the progression bar!
*   **Command-Driven Battle System:** Everything is a Skill. Even basic attacks are skills in the newly updated system.
*   **Highest-Priority Skill Execution:** Skills with higher priority (e.g. signature skills) are executed over basic attacks when charged.
*   **Procedural Elite Monster System:** Monsters have a chance to spawn as Elite variants with 1.5x stats, a signature skill, and "[Elite]" title.
*   **Elite Loot Bias:** Defeating Elite monsters generates better loot through a new bias value system.
*   **Data-Driven Ascii Art (File I/O):** ASCII components for monsters are dynamically loaded from external text files.
*   **Condition-Based Skill System:** Introduces an advanced trigger system (`ON_TURN_START`, `ON_ATTACK`, `ON_DEFEND`) for dynamically activating class skills.
*   **Dynamic LUCK Probability Algorithm:** Implements an advantage/disadvantage system to impact probability rolls for combat skills.
*   **Temporary Battle Buff System:** Stat modifiers can now be dynamically altered through buffs and accurately reset after every encounter.
*   **Strategy Pattern Job System & 10x Stat Scaling:** Jobs like Melee Dealer, Range Dealer, Tanker, and Healer are implemented as strategies providing dynamic stat multipliers. All baseline stats are scaled by 10x for precision.
*   **DEF-based Damage Reduction Formula:** Taking damage now effectively reduces impact based on Defense via `100.0 / (100.0 + DEF)` reduction formula.
*   **Item Appraisal & Gate Loot Box System:** Dropped items are no longer instantly equipped but instead safely stored. At the end of a gate, a dedicated Appraisal UI phase allows carefully comparing and selecting items.
*   **Gate Progression Visuals & Battle Impact UX:** Clear visual indicators displaying your progression in a gate (`[Entrance] -> [*YOU*] -> [M2] -> [Clear]`). Attacks are emphasized with slight delay ticks and ASCII action text (e.g. `/// SLASH ///`, `*** SMASH ***`).
*   **Procedural Monster Generation:** Both the names and the ASCII art of monsters are dynamically generated based on their stats (ATK, DEF, SPD, MAX HP). Every monster is uniquely assembled from a variety of prefixes, suffixes, elements, tribes, and visual components.
*   **Multiple Character Classes:** Choose from 5 distinct classes, each with its own stat bonuses and starting stats:
    *   Melee Dealer
    *   Range Dealer
    *   Spell Dealer
    *   Tanker
    *   Healer
*   **Gate Selection:** Choose your difficulty every turn by entering different types of gates (Green, Yellow, Red, Chaos). Higher risk yields greater rewards (and tougher monsters).
*   **Turn-based Combat:** Strategic battles where speed determines who attacks first. Defeat monsters to gain EXP, level up, and increase your stats.
*   **Modular Architecture:** The codebase is cleanly separated into distinct modules (`Game`, `Player`, `Monster`, `Battle`, `UI`, `AsciiArtManager`) for easy extensibility and maintenance.

## Project Structure

*   `HunterRPG/HunterRPG.cpp`: The entry point of the application.
*   `HunterRPG/Game.cpp`, `.h`: Manages the core game loop, player creation, and turn progression.
*   `HunterRPG/AsciiArtManager.cpp`, `.h`: Handles the procedural generation of ASCII art for monsters and the game title.
*   `HunterRPG/Player.cpp`, `.h`: Represents the player character, stats, leveling, and loot.
*   `HunterRPG/Monster.cpp`, `.h`: Represents enemy characters and their procedural naming logic.
*   `HunterRPG/Battle.cpp`, `.h`: Manages the combat logic between a Player and a Monster.
*   `HunterRPG/UI.cpp`, `.h`: Handles all text-based UI rendering, including menus, status screens, and health bars.
*   `HunterRPG/Job.h`: Handles the dynamic multiplier strategy implementations for Character classes.

## How to Build and Run

### Prerequisites

*   A C++ compiler that supports C++14 or later (e.g., GCC, Clang, MSVC).

### Compilation (Linux / macOS / WSL)

Open a terminal in the project root directory and run the following command:

```bash
g++ -std=c++14 HunterRPG/*.cpp -o game
```

### Execution

After compiling, run the executable:

```bash
./game
```
