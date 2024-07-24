/* @Author
* Student Name: EREN CULHACI
* Student ID : 150220763
*/

#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>
#include <cstdlib>

class Pokemon {

    public:
    Pokemon(std::string, int, int, float, int); //Constructor with 5 variables, "string name", "int HP", "int damage", "float powerup_chance", "int recharge"
    void set_HP(int); //setter for HP

    std::string get_name() const; //getter for name
    int get_HP() const; //getter for HP
    int get_damage() const; //getter for damage
    float get_powerup_chance() const; //getter for powerup_change
    int get_recharge() const; //getter for recharge
    
    bool powerup_state() const; //state checker if pokemon is on powerup state


    private:
    const std::string name;
    int HP;
    const int damage;
    const float powerup_chance;
    const int recharge;
};

#endif // POKEMON_H

