# Hunter RPG

Hunter RPG is a text-based C++ Role-Playing Game (MUD style) where you step into the shoes of a newly awakened Hunter.

Explore different gates, battle procedurally generated monsters, and survive as long as you can!

## Features

*   **Procedural Monster Generation:** Both the names and the ASCII art of monsters are dynamically generated based on their stats (ATK, DEF, SPD, MAX HP). Every monster is uniquely assembled from a variety of prefixes, suffixes, elements, tribes, and visual components (heads, bodies, weapons, legs).
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
