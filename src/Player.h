#pragma once
#include "Map.h"
#include "Cards.h"
#include "Orders.h"

class Order;
class Territory;
class Graph;

class Player {
private:
 // Vector of pointers of territories
 std::vector<Territory*> ownedTerritories;
 // Vector of pointers of cards
 std::vector<Card*> handOfCards;
 // Vector of pointers of orders
 std::vector<Order*> listOfOrders;

public:
 // Default constructor
 Player();
 // Parametric constructor
 Player(std::vector<Territory*> terr); 
 // Copy constructor
 Player(const Player& pCopy);
 // Destructor
 ~Player();
 // Assignment operator
 Player& operator =(const Player& p);
 // Stream insertion operator
 friend std::ostream& operator<<(std::ostream& out, const Player& toOutput);

 // Will return a vector of pointers of territories to defend
 std::vector<Territory*> toDefend();
 // Will return a vector of pointers of territories to attack
 std::vector<Territory*> toAttack(Graph& graph);   
 // Will create an Order object and add it to the vector of pointers of orders
 void issueOrder();

 // Additional methods
 void AddTerritoryToPlayer(Territory* territoryToAdd);
 void AddCardToPlayer(Card* cardToAdd);
 void AddOrderToPlayer(Order* orderToAdd);
};