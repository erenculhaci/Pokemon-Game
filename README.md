# Pokémon Battle Game

This project implements a Pokémon battle simulation featuring two specific types of Pokémon: ElectricPokémon and PsychicPokémon. The simulation takes place in an arena that can influence the battle based on its terrain type. This README provides an overview of the classes and methods involved in the implementation.

## Classes Overview

### 1. Pokémon
The `Pokemon` class represents a generic Pokémon with the following attributes:

- **Name**: The name of the Pokémon (e.g., "Pikachu").
- **Hit Points (HP)**: The amount of damage a Pokémon can take before fainting.
- **Damage**: The amount of damage a Pokémon inflicts in each round of battle.
- **PowerUp Chance**: The probability of the Pokémon powering up in a round.
- **Recharge**: The number of rounds a Pokémon must wait before attempting to power up again.

Each Pokémon also has internal state variables, such as whether it has fainted, whether it is currently powered up, and whether it is on its own terrain.

### 2. ElectricPokémon
The `ElectricPokemon` class inherits from `Pokemon` and has specialized abilities:

- **PowerUp Chance**: 20%.
- **PowerUp Effect**: Deals 300% of its regular damage when powered up.
- **Recharge Time**: 3 rounds.
- **Special Condition**: Can be confused, When it is confused, it may attempt to perform attacks and PowerUps as usual, however, the attacks result in no damage to its opponent for three rounds. Immune to confusion when on electric terrain.

### 3. PsychicPokémon
The `PsychicPokemon` class also inherits from `Pokemon` and has its own abilities:

- **PowerUp Chance**: 30%.
- **PowerUp Effect**: Can confuse opponents and deals regular damage.
- **Recharge Time**: 5 rounds.
- **Special Condition**: Immune to confusion. Can deal double damage when on psychic terrain.

### 4. Arena
The `Arena` class manages the battle between one `ElectricPokemon` and one `PsychicPokemon`. The arena can have three types of terrain: Electric, Psychic, or None, which influence the battle. The terrain can vary throughout a battle and the state of terrain is reset at the beginning of each battle.

#### Key Methods:
- `void addPokemon(char type, string name, int hp, int damage)`: A battle can be conducted if one PsychicPokemon and one ElectricPokemon are in the arena. The addPokemon method takes as arguments the type of Pokemon (’e’ for electric, ’p’ for psychic), the name of the Pokemon, the HP and damage.
- `void simulateBattle()`: Simulates the battle between the two Pokémon.
- `void spawnTerrain()`: Randomly spawns terrain. Electric and psychic terrains can be spawned with 20% chance each and there is a 60% chance that the terrain type is none. If either electric or psychic terrains have been spawned, the arena retains this terrain for 5 rounds. At the end of the 5 rounds, a terrain is spawned again. If the terrain spawned is none, then the spawn attempt is repeated in the next round without retention.
- `void restartTerrain()`: Resets the terrain when new Pokémon enter the arena.
- `void printRoundStats(int round, int heads)`: Prints the status of the battle at the end of each round.
- `void printMatchResults()`: Prints the final results of the battle.

## Battle Mechanics

- Pokémon take turns attacking each other until one faints.
- The first Pokémon to attack each round is determined randomly.
- Terrain affects the performance of Pokémon (e.g., Electric terrain boosts ElectricPokémon).

## Output

At the end of each round, the battle's status is printed, including the remaining HP of each Pokémon, the current terrain, and any special conditions (like confusion). The final results are displayed at the end of the match.

## Usage

To run the simulation, instantiate the `Arena` class, add the Pokémon using `addPokemon()`, and call `simulateBattle()` to start the battle.

## Building and Running the Code

You can build and run the code with the following command:
```
$ g++ -Wall -Werror src/pokemon.cpp src/arena.cpp src/electricPokemon.cpp src/psychicPokemon.cpp src/main.cpp -I include -o pokemongame

$ ./pokemongame
```

## UML Diagram of Classes

![UML DIAGRAM](https://github.com/user-attachments/assets/85288546-8196-4b48-9965-bddac1dfdb2d)

