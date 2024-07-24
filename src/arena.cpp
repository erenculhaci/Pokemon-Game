/* @Author
* Student Name: EREN CULHACI
* Student ID : 150220763
*/

#include "arena.h"

    Arena::Arena(){ //constructor for arena
        terrain = "none"; //terrain is default "none"
        electricpoke = nullptr; //electricpoke default nullptr
        psychicpoke = nullptr;//psychicpoke default nullptr
    }

    void Arena::addPokemon(char type, std::string name, int hp, int damage){ //adding pokemon method takes one type character, one name string, hp and damage integers
        if (type=='e'){ //if type is electric
            std::cout << "Electric Pokemon " << name << " has entered the arena."  << std::endl; //It prints electric pokemon has entered the arena 
            std::cout << "Class: Electric" << std::endl << "        Name: " << name << std::endl << "        HP: " << hp << std::endl << "        Damage: " << damage << std::endl << std::endl << std::endl; //It prints it's class, name, HP and damage.
            delete electricpoke; //frees the memory before creating new object            
            electricpoke = new ElectricPokemon(name, hp, damage); //it creates a ElectricPokemon object dynamically with given name, hp, damage
        } 
        else if (type=='p'){ //if type is psychic
            std::cout << "Psychic Pokemon " << name << " has entered the arena."  << std::endl; //It prints psychic pokemon has entered the arena 
            std::cout << "Class: Psychic" << std::endl << "        Name: " << name << std::endl << "        HP: " << hp << std::endl << "        Damage: " << damage << std::endl << std::endl << std::endl; //It prints it's class, name, HP and damage.
            delete psychicpoke; //frees the memory before creating new object         
            psychicpoke = new PsychicPokemon(name, hp, damage); //it creates a PsychicPokemon object dynamically with given name, hp, damage
        }

        restartTerrain(); //it restarts the terrain when a new pokemon added to the arena
    }


    void Arena::simulateBattle(){
        int wait_time_electric = 0; //electric powerup state wait duration
        int wait_time_psychic = 0; //psychic powerup state wait duration
        bool electric_power = 0; //electric powerup state flag
        bool psychic_power = 0; //psychic powerup state flag.
        int confusion_wait = 0; //confusion effect waiting duration
        int heads = 0; //heads for deciding which pokemon goes first in that round.
        int spawn_wait_time = 1; //terrain spawning waiting time

        for (int round = 1; electricpoke->get_HP() > 0 && psychicpoke->get_HP() > 0; round++){ //rounds incrementing until one pokemon is fainted

                printRoundStats(round,heads); //prints the round stats.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                if(wait_time_electric == 0 && electricpoke->powerup_state()){ //if electric state waiting time is zero and electricpokemon power state is true, 
                    electric_power = 1; //electric powerup state is 1
                    wait_time_electric = electricpoke->get_recharge(); //electric powerup state waiting time is set to recharge.
                    std::cout << electricpoke->get_name() <<" has initiated a power up." << std::endl;  //prints electric pokemon has initiated a powerup on screen.
                }
                else{ // waiting time for electric is not zero or electricpoke powerup state is 0, 
                    electric_power = 0; //electric powerup state is 0
                    wait_time_electric--; //decrement waitingtime for electric powerup state
                    if (wait_time_electric <=0){ //if waiting time state goes below zero make it equal to zero.
                        wait_time_electric = 0;
                    }
                }

                if(wait_time_psychic == 0 && psychicpoke->powerup_state()){ //if waiting time psychic is 0 and psychic powerup state is 1,
                    confusion_wait = 0; //there is no confusion in the round the powerup initiated (but there is confusion after three rounds of this round).
                    psychic_power = 1; //make psychic power 1.
                    wait_time_psychic = psychicpoke->get_recharge(); //make waiting time for psychic to recharge value of psychic pokemon.
                    std::cout << psychicpoke->get_name() <<" has initiated a power up." << std::endl;  // print that pokemon has initiated powerup.
                }
                else if(wait_time_psychic == psychicpoke->get_recharge() - 1 && psychic_power == 1){ //after the round of the initialization of powerup
                    psychic_power = 0;//turn psychic power 0
                    confusion_wait = 2; //make 3 rounds confusion. (It is 2 because it decrements to 0)
                }
                else{// if waiting time psychic is not zero or psychic powerup state is zero
                    if(confusion_wait != 0){ //if confusion waiting is not zero
                        confusion_wait--; //decrement confusion waiting
                        if(confusion_wait <= 0){ //if confusion waiting is below zero
                            confusion_wait = 0; //make it zero
                        }
                    }
                    wait_time_psychic--; //decrement waiting time for psychic state.
                    if(wait_time_psychic <= 0){//if waiting time for psychic is below zero
                        wait_time_psychic = 0; //make it zero.
                    }
                }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if(heads == 1){ //if electric pokemon starts first
            if(terrain == "none"){ //if current terrain is "none"
                if(electric_power && confusion_wait == 0){ // if electricpowerup state is 1 and there is no confusion wait, 
                    
                    psychicpoke->set_HP(psychicpoke->get_HP() - (electricpoke->get_damage()*3)); //electric pokemon deals 3x damage.
                    if(psychicpoke->get_HP() <= 0){ // if psychic pokemon's hp goes below 0
                        psychicpoke->set_HP(0);// make it zero
                        printMatchResults();//print match results
                        break; //end match
                    }

                    electricpoke->set_HP(electricpoke->get_HP() - psychicpoke->get_damage()); //psychic pokemon deals normal damage
                    if(electricpoke->get_HP() <= 0){ //if electric pokemon hp goes below zero
                        electricpoke->set_HP(0); //make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }
                }
                else if(!electric_power && confusion_wait == 0){ //if electric pokemon is not in powerup state and confusion waiting is on zero
                    psychicpoke->set_HP(psychicpoke->get_HP() - (electricpoke->get_damage())); //electric pokemon deals normal damage
                    if(psychicpoke->get_HP() <= 0){ //if psychic pokemon hp goes below zero
                        psychicpoke->set_HP(0); //make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }

                    electricpoke->set_HP(electricpoke->get_HP() - psychicpoke->get_damage()); //psychic pokemon deals normal damage
                    if(electricpoke->get_HP() <= 0){ // if electric pokemon hp goes below zero
                        electricpoke->set_HP(0); //make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }
                    
                }
                else{ //if electric pokemon is confused,
                    psychicpoke->set_HP(psychicpoke->get_HP()); //electric pokemon doesnt deal damage.
                    if(psychicpoke->get_HP() <= 0){ //if psychic pokemon hp goes below zero
                        psychicpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }
                    electricpoke->set_HP(electricpoke->get_HP() - psychicpoke->get_damage()); //psychic pokemon deals normal damage
                    if(electricpoke->get_HP() <= 0){ //if electric pokemon hp goes below zero
                        electricpoke->set_HP(0); //make it zero.
                        printMatchResults(); //print match results
                        break; //end match
                    }
                    
                }                
            }

            if(terrain == "psychic"){ // if current terrain is psychic, 

                if(electric_power && confusion_wait == 0){ //if electric powerup is 1 and there is no confusion wait,
                    psychicpoke->set_HP(psychicpoke->get_HP() - (electricpoke->get_damage()*3)); //electric pokemon deals 3x damage.
                    if(psychicpoke->get_HP() <= 0){ //if psychic pokemon hp goes below zero
                        psychicpoke->set_HP(0); //make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }

                    electricpoke->set_HP(electricpoke->get_HP() - (psychicpoke->get_damage()*2)); //psychic pokemon deals 2x damage
                    if(electricpoke->get_HP() <= 0){ //if electric pokemon hp goes below zero
                        electricpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }

                }
                else if(!electric_power && confusion_wait == 0){ // if electric powerup state is not 1, and there is no confusion wait
                    psychicpoke->set_HP(psychicpoke->get_HP() - (electricpoke->get_damage())); //electric pokemon deals normal damage
                    if(psychicpoke->get_HP() <= 0){ //if psychic pokemon hp goes below zero
                        psychicpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }

                    electricpoke->set_HP(electricpoke->get_HP() - (psychicpoke->get_damage()*2)); //psychic pokemon deals 2x damage
                    if(electricpoke->get_HP() <= 0){ //if electric pokemon hp goes below zero
                        electricpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }
                    
                }
                else{ //if electric pokemon is confused
                    psychicpoke->set_HP(psychicpoke->get_HP()); //electric pokemon doesn't deal damage
                    if(psychicpoke->get_HP() <= 0){ //if psychic pokemon hp goes below zero
                        psychicpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }

                    electricpoke->set_HP(electricpoke->get_HP() - (psychicpoke->get_damage()*2)); //psychic pokemon deals 2x damage.
                    if(electricpoke->get_HP() <= 0){ //if electric pokemon hp goes below zero
                        electricpoke->set_HP(0); //make it zero
                        printMatchResults(); //print match results
                        break; //end match               
                    }
                    
                } 
            }

            if(terrain == "electric"){ //if current terrain is electric

                if(electric_power){ //if electric powerup state is 1, 
                    psychicpoke->set_HP(psychicpoke->get_HP() - (electricpoke->get_damage()*3)); //electric pokemon deals 3x damage
                    if(psychicpoke->get_HP() <= 0){ //if psychic pokemon hp goes below zero
                        psychicpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }

                    electricpoke->set_HP(electricpoke->get_HP() - psychicpoke->get_damage()); //psychic pokemon deals normal damage.
                    if(electricpoke->get_HP() <= 0){ //if electric pokemon hp goes below zero
                        electricpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }
                    
                }
                else{ // if electric powerup state is not 1,
                    psychicpoke->set_HP(psychicpoke->get_HP() - electricpoke->get_damage()); //electric pokemon deals normal damage
                    if(psychicpoke->get_HP() <= 0){ //if psychic pokemon hp goes below zero
                        psychicpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }

                    electricpoke->set_HP(electricpoke->get_HP() - psychicpoke->get_damage()); //psychic pokemon deals normal damage
                    if(electricpoke->get_HP() <= 0){ //if electric pokemon hp goes below zero
                        electricpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }
                }                
            }
        }
        else{ //if psychic pokemon goes first in this round, 
            if(terrain == "none"){ //if current terrain is none,

                if(electric_power && confusion_wait == 0){ //if electric powerup state is 1, and there is no confusion waiting
                    electricpoke->set_HP(electricpoke->get_HP() - psychicpoke->get_damage()); //psychic pokemon deals normal damage
                    if(electricpoke->get_HP() <= 0){ //if electric pokemon hp goes below zero
                        electricpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }

                    psychicpoke->set_HP(psychicpoke->get_HP() - (electricpoke->get_damage()*3)); //electric pokemon deals 3x damage.
                    if(psychicpoke->get_HP() <= 0){ //if psychic pokemon hp goes below zero
                        psychicpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }
                }
                else if(!electric_power && confusion_wait == 0){ //if there is no electric powerup state and confusion waiting
                    
                    electricpoke->set_HP(electricpoke->get_HP() - psychicpoke->get_damage()); //psychic pokemon deals normal damage
                    if(electricpoke->get_HP() <= 0){ //if electric pokemon hp goes below zero
                        electricpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }

                    psychicpoke->set_HP(psychicpoke->get_HP() - (electricpoke->get_damage())); //electric pokemon deals normal damage
                    if(psychicpoke->get_HP() <= 0){ //if psychic pokemon hp goes below zero
                        psychicpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }
                }
                else{ //if electric pokemon is confused
                    
                    electricpoke->set_HP(electricpoke->get_HP() - psychicpoke->get_damage()); //psychic pokemon deals normal damage
                    if(electricpoke->get_HP() <= 0){ //if electric pokemon hp goes below zero
                        electricpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }

                    psychicpoke->set_HP(psychicpoke->get_HP()); //electric pokemon doesn't deal damage
                    if(psychicpoke->get_HP() <= 0){ //if psychic pokemon hp goes below zero
                        psychicpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }
                }                
            }

            if(terrain == "psychic"){ //if current terrain is psychic

                if(electric_power && confusion_wait == 0){ //if electric powerup state is 1 and there is no confusion wait
                    
                    electricpoke->set_HP(electricpoke->get_HP() - (psychicpoke->get_damage()*2)); //psychic pokemon deals 2x damage
                    if(electricpoke->get_HP() <= 0){ //if electric pokemon hp goes below zero
                        electricpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }

                    psychicpoke->set_HP(psychicpoke->get_HP() - (electricpoke->get_damage()*3)); //electric pokemon deals 3x damage
                    if(psychicpoke->get_HP() <= 0){ //if psychic pokemon hp goes below zero
                        psychicpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }
                }
                else if(!electric_power && confusion_wait == 0){ //if there is no electric powerup state and confusion waiting
                    
                    electricpoke->set_HP(electricpoke->get_HP() - (psychicpoke->get_damage()*2)); //psychic pokemon deals 2x damage
                    if(electricpoke->get_HP() <= 0){ //if electric pokemon hp goes below zero
                        electricpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }

                    psychicpoke->set_HP(psychicpoke->get_HP() - (electricpoke->get_damage())); //electric pokemon deals normal damage
                    if(psychicpoke->get_HP() <= 0){ //if psychic pokemon hp goes below zero
                        psychicpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }
                }
                else{ //if electric pokemon is confused
                    electricpoke->set_HP(electricpoke->get_HP() - (psychicpoke->get_damage()*2)); //psychic pokemon deals 2x damage
                    if(electricpoke->get_HP() <= 0){ //if electric pokemon hp goes below zero
                        electricpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }

                    psychicpoke->set_HP(psychicpoke->get_HP()); //electric pokemon doesn't deal any damage.
                    if(psychicpoke->get_HP() <= 0){ //if psychic pokemon hp goes below zero
                        psychicpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }
                } 
            }

            if(terrain == "electric"){ //if the current terrain is electric

                if(electric_power){ //if electric powerup state is 1,
                    electricpoke->set_HP(electricpoke->get_HP() - psychicpoke->get_damage()); //psychic pokemon deals normal damage
                    if(electricpoke->get_HP() <= 0){ //if electric pokemon hp goes below zero
                        electricpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }

                    psychicpoke->set_HP(psychicpoke->get_HP() - (electricpoke->get_damage()*3)); //electric pokemon deals 3x damage
                    if(psychicpoke->get_HP() <= 0){ //if psychic pokemon hp goes below zero
                        psychicpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }
                }
                else{ //if electric powerup state is 0, 
                    electricpoke->set_HP(electricpoke->get_HP() - psychicpoke->get_damage()); //psychic pokemon deals normal damage
                    if(electricpoke->get_HP() <= 0){ //if electric pokemon hp goes below zero
                        electricpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }

                    psychicpoke->set_HP(psychicpoke->get_HP() - electricpoke->get_damage()); //electric pokemon deals normal damage
                    if(psychicpoke->get_HP() <= 0){ //if psychic pokemon hp goes below zero
                        psychicpoke->set_HP(0);//make it zero
                        printMatchResults(); //print match results
                        break; //end match
                    }
                }                
            }
        }
            

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            printMatchResults(); //print match results

            if(electricpoke->get_HP() == 0 && psychicpoke ->get_HP() == 0){ //if both hps are 0,
                if(heads == 0){ //if psychic pokemon started that round
                    std::cout << "Match Results: " << std::endl << psychicpoke->get_name() << " has won the match!" << std::endl << std::endl << std::endl; //prints that psychic pokemon has won
                }
                else{ //if electric pokemon started that round
                    std::cout << "Match Results: " << std::endl << electricpoke->get_name() << " has won the match!" << std::endl << std::endl << std::endl; //prints that electric pokemon has won
                }   
        }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            if(terrain == "psychic" || terrain == "electric"){ //if terrain is psychic or electric
                if(spawn_wait_time==1){ //if waiting time is 1, 
                    spawn_wait_time = 5; //make it 5           
                }
                else{// if waiting time is not 1, 
                    spawn_wait_time--; //decrement the waiting time for spawn
                    if(spawn_wait_time == 1){ //if waiting time for spawn reaches 1, 
                        spawnTerrain(); //spawn terrain
                    }
                }
            }
            else{ //if terrain is none
                spawnTerrain(); //spawn terrain
            }
        
        }        
    }

    void Arena::spawnTerrain(){ //terrain spawning method
        int rand_num = rand() % 100 + 1; // generate a random number between 1 and 100

            if (rand_num <= 20) { //if random number is under 20
                terrain = "psychic"; //make terrain psychic
            }
            else if (rand_num <= 40) { //if random number is under 40 and bigger than 20
                terrain = "electric"; //make terrain electric
            }
            else { //if random number is between 40-100
                terrain = "none"; //make terrain none
            }
    }
    void Arena::restartTerrain(){ //terrain spawner after adding pokemon
        int rand_num = rand() % 100 + 1; // generate a random number between 1 and 100

            if (rand_num <= 20) { //if random number is under 20
                terrain = "psychic"; //make terrain psychic
            }
            else if (rand_num <= 40) { //if random number is under 40 and bigger than 20
                terrain = "electric"; //make terrain electric
            }
            else { //if random number is between 40-100
                terrain = "none"; //make terrain none
            }
    }
    void Arena::printRoundStats(const int rounds, int& heads) const{ //prints the round stats
        std::cout << "Round: " << rounds << std::endl; //prints the round
        std::cout << "Current Terrain: " << terrain << std::endl; //prints the current terrain

        heads = rand() % 2; //generates random number 0 or 1
        if (heads == 0) { //if random number heads is 0
            std::cout << psychicpoke->get_name() << " goes first." << std::endl; //prints psychic pokemon goes first.
        } 
        else { //if random number heads is 1, 
            std::cout << electricpoke->get_name() << " goes first." << std::endl; //prints electric pokemon goes first
        }

    }
    void Arena::printMatchResults() const{ //prints the match results
        std::cout << electricpoke->get_name() << " HP: " << electricpoke->get_HP() << std::endl; //prints electric pokemon hp
        std::cout << psychicpoke->get_name() << " HP: " << psychicpoke->get_HP() << std::endl; //prints psychic pokemon hp
        if(electricpoke->get_HP() > psychicpoke->get_HP()){ //if electric pokemon hp is more than psychic pokemon,
            std::cout << electricpoke->get_name() << " is in the lead!" << std::endl << std::endl << std::endl; //prints electric pokemon is in the lead
        }
        else if (electricpoke->get_HP() < psychicpoke->get_HP()){ //if electric pokemon hp is lower than psychic pokemon,
            std::cout << psychicpoke->get_name() << " is in the lead!" << std::endl << std::endl << std::endl; //prints psychic pokemon is in the lead
        }
        else { //if both hp's are same at that round
            std::cout << "No pokemon is in the lead!" << std::endl << std::endl << std::endl; //prints that no pokemon is in the lead.
        }

        if(electricpoke->get_HP() == 0 && psychicpoke->get_HP() != 0){ //if electric pokemon's hp is 0 but psychic pokemon's hp is not zero,
            std::cout << "Match Results: " << std::endl << psychicpoke->get_name() << " has won the match!" << std::endl << std::endl << std::endl; //prints psychic pokemon has won the match as match result
        }
        else if(psychicpoke->get_HP() == 0 && electricpoke->get_HP() != 0){ //if psycic pokemon's hp is 0 but electric pokemon's hp is not zero,
            std::cout << "Match Results: " << std::endl << electricpoke->get_name() << " has won the match!" << std::endl << std::endl << std::endl; //prints electric pokemon has won the match as match result
        }
    }

    Arena::~Arena(){ //Arena destructor
        delete electricpoke; //deletes electricpoke,
        delete psychicpoke; //deletes psychicpoke,
    }
