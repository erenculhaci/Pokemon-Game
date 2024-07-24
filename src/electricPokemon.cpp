/* @Author
* Student Name: EREN CULHACI
* Student ID : 150220763
*/

#include "electricPokemon.h"

ElectricPokemon::ElectricPokemon(std::string name, int hp, int damage): Pokemon(name, hp, damage, 0.2, 3) {}
//Constructor. It uses Pokemon class constructor to initialize attributes. First three attribute can be changed but powerup_chance and recharge is 0.2, 3 respectively.

        bool ElectricPokemon::isFainted() const{
            if(get_HP() == 0){ //if HP is zero
                return true; // fainted
            }
            else{
                return false;// not fainted
            }
        }

        bool ElectricPokemon::isOnTerrain(std::string terrain) const{
            if(terrain == "electric"){ //if terrain is electric
                return true; //current terrain is electric
            }
            else{
                return false; //current terrain is not electric
            }
        }