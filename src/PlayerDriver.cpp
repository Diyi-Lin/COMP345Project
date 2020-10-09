#include "Player.h"
#include "Map.h"
#include "Orders.h"

#define PLAYER_DRIVER
#ifdef PLAYER_DRIVER

int main() {

    // Creating Territories
    Territory* terr1 = new Territory("A"); 
    Territory* terr2 = new Territory("B");
    Territory* terr3 = new Territory("C");
    std::vector<Territory*> territories { terr1, terr2, terr3 };
    // Creating continents
    Continent c[] = {
      Continent(1, std::string("W")),
      Continent(2, std::string("X"))
    };
    // Adding territories to continents
    c[0].AddTerritory(terr1);
    c[1].AddTerritory(terr2);
    c[1].AddTerritory(terr3);
    // Pointer to a vector of pointers of continents
    std::vector<Continent*> continents({ &c[0], &c[1] });

    // Creating a Map from the 2 continents and adding the territories to it
    Map* map = new Map(2, continents);
    map->AddTerritory(terr1);
    map->AddTerritory(terr2);
    map->AddTerritory(terr3);

    // Creating Player object with default constructor
    Player* p1 = new Player();
    std::cout << "Player p1: " << *p1 << std::endl;

    // Adding a territory to p1
    p1->AddTerritoryToPlayer(terr1);

    // Creating a Player object with copy constructor
    Player *p2 = new Player(*p1);
    std::cout << "Player p2: " << *p2 << std::endl;
   
   // Adding a territory to p2
    p2->AddTerritoryToPlayer(terr2);
    std::cout << "Player p1: " << *p1 << std::endl;
    std::cout << "Player p2: " << *p2 << std::endl;

    // Creating a Player object with parametric constructor
    Player* p3 = new Player(territories);
    std::cout << "Player p3: " << *p3 << std::endl;

    // Adding an order (deploy by example)
    p1->issueOrder();
    // Creating and adding a card
    Card* card1 = new Card(0);
    p1->AddCardToPlayer(card1);

    // Assignment operator
    Player* p4 = p1;
    std::cout << "Player p1: " << *p1 << std::endl;
    std::cout << "Player p4: " << *p4 << std::endl;

    // Displaying p1's territories to defend (should be A)
    std::vector<Territory*> terrToDefend = p1->toDefend();
    std::cout << "Player p1's territories to defend:" << std::endl;
    for (Territory* t : terrToDefend)
        std::cout << (t->GetName()) << std::endl;

    // Displaying p1's territories to attack (should be B and C)
    std::vector<Territory*> terrToAttack = p1->toAttack(*map);
    std::cout << "\nPlayer p1's territories to attack:" << std::endl;
    for (Territory* t : terrToAttack)
        std::cout << (t->GetName()) << std::endl;

    // Deleting everything
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete terr1;
    delete terr2;
    delete terr3;
    delete map;
    delete card1;

    p1 = nullptr;
    p2 = nullptr;
    p3 = nullptr;
    p4 = nullptr;
    terr1 = nullptr;
    terr2 = nullptr;
    terr3 = nullptr;
    map = nullptr;
    card1 = nullptr;
};

#endif
