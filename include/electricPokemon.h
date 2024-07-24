/* @Author
* Student Name: EREN CULHACI
* Student ID : 150220763
*/
#ifndef ELECTRIC_POKEMON_H
#define ELECTRIC_POKEMON_H

#include "pokemon.h"

class ElectricPokemon : public Pokemon { //ElectricPokemon class inherited from Pokemon. (Public inheritence)
    public:
        ElectricPokemon(std::string, int, int); //Constructor with 3 variables, "string name" "int hp" "int damage"
        bool isFainted() const; //checks if pokemon's health is 0
        bool isOnTerrain(std::string) const; //checks if electric pokemon is on electric terrain (own terrain) takes one strings indicates the current terrain 
};

#endif // ELECTRIC_POKEMON_H