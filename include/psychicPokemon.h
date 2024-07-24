/* @Author
* Student Name: EREN CULHACI
* Student ID : 150220763
*/
#ifndef PSYCHIC_POKEMON_H
#define PSYCHIC_POKEMON_H

#include "pokemon.h"

class PsychicPokemon : public Pokemon { //PsychicPokemon class inherited from Pokemon. (Public inheritence)
    public:
        PsychicPokemon(std::string, int, int); //Constructor with 3 variables, "string name" "int hp" "int damage"
        bool isFainted() const; //checks if pokemon's health is 0
        bool isOnTerrain(std::string) const; //checks if psychic pokemon is on psychic terrain (own terrain) takes one strings indicates the current terrain 
};

#endif // PSYCHIC_POKEMON_H