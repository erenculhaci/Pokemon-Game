/* @Author
* Student Name: EREN CULHACI
* Student ID : 150220763
*/
#include "pokemon.h"
Pokemon::Pokemon(std::string poke_name, int hp, int dmg, float power_chance, int charge) :name{poke_name}, HP{hp}, damage{dmg}, powerup_chance{power_chance}, recharge{charge}{};
//Constructor for pokemon with 5 variables. It uses initializer.
    
    void Pokemon::set_HP(int hp){ //setter for HP
        HP = hp;
    }

    std::string Pokemon::get_name() const{ //getter for name
        return name;
    }
    int Pokemon::get_HP() const{ //getter for HP
        return HP;
    }
    int Pokemon::get_damage() const{ //getter for damage
        return damage;
    }

    float Pokemon::get_powerup_chance() const{ //getter for powerup_chance
        return powerup_chance;
    }
    int Pokemon::get_recharge() const{ //getter for recharge
        return recharge;
    }

    bool Pokemon::powerup_state() const{
        int random_number = rand() % 100 + 1; // Generate a random number between 1 and 100
        
        if (random_number <= (get_powerup_chance()*100)) { // Check if the random integer is less than or equal to the powerup chance.
            return true; // Return true with the given chance
        }
        else {
            return false; // Return false with the complementary chance
        }
    }