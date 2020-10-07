#include "Player.h"

#define PLAYER_DRIVER
#ifdef PLAYER_DRIVER

int main() {

    // Creating Player object with default constructors
    Player* p1 = new Player();
    std::cout << p1 << std::endl;

    // Adding a territory to p1
    Territory* terr1 = new Territory(&std::string("A"));
    p1->AddTerritoryToPlayer(terr1);

    // Creating a Player object with copy constructor
    Player *p2 = new Player(*p1);
    std::cout << p2 << std::endl;

    // Adding an order to p1 (deploy by example)
    p1->issueOrder();

}


#endif