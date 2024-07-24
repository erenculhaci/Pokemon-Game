/* @Author
* Student Name: EREN CULHACI
* Student ID : 150220763
*/

#include "psychicPokemon.h"

PsychicPokemon::PsychicPokemon(std::string name, int hp, int damage): Pokemon(name, hp, damage, 0.3, 5) {}
//Constructor. It uses Pokemon class constructor to initialize attributes. First three attribute can be changed but powerup_chance and recharge is 0.3, 5 respectively.

        bool PsychicPokemon::isFainted() const{ //checks if pokemon is fainted or not
            if(get_HP() == 0){ //if HP is zero
                return true;// pokemon is fainted
            }
            else{
                return false; //else not
            }
        }

        bool PsychicPokemon::isOnTerrain(std::string terrain) const{ //checks if terrain is psychic or not.
            if(terrain == "psychic"){ //if terrain is psychic
                return true; // the flag is true
            }
            else{
                return false; //else not
            }
        }