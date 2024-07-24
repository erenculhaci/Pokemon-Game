/* @Author
* Student Name: EREN CULHACI
* Student ID : 150220763
*/
#ifndef ARENA_H
#define ARENA_H

#include "electricPokemon.h"
#include "psychicPokemon.h"

class Arena {
    public:
        Arena(); //Arena default constructor
        void addPokemon(char, std::string, int, int); //addPokemon adds pokemons to the arena. If char is p, it adds psychic, if e, it adds electric pokemon. It has a string name, integer hp and integer damage attributes.
        void simulateBattle(); //simulates the battle
        void spawnTerrain(); // spawns the terrain
        void restartTerrain();// restarts terrain if new pokemon added
        void printRoundStats(const int, int&) const; //prints the stats of round each round
        void printMatchResults() const; //prints the results of match
        ~Arena();//arena destructor to delete pointers

    private:
        std::string terrain; //terrain name
        ElectricPokemon* electricpoke; //electric pokemon pointer
        PsychicPokemon* psychicpoke; //psychic pokemon pointer.
};

#endif //ARENA_H