#include "Player.h"

// Default constructor
Player::Player() : ownedTerritories(std::vector<Territory*>(0)), 
    handOfCards(std::vector<Card*>(0)), 
    listOfOrders(std::vector<Order*>(0)) 
{}
// Parametric constructor
Player::Player(std::vector<Territory*> terr) : ownedTerritories(terr) {}

// Copy constructor MAKE DEEP COPY AOUH
Player::Player(const Player& pCopy) {
    ownedTerritories = pCopy.ownedTerritories;
    handOfCards = pCopy.handOfCards;
    listOfOrders = pCopy.listOfOrders;
}

// Assignment operator
Player& Player::operator= (const Player& rightP) {
    if (&rightP != this) {
        ownedTerritories = rightP.ownedTerritories;
        handOfCards = rightP.handOfCards;
        listOfOrders = rightP.listOfOrders;
    }
    return *this;
}
// Destructor
Player::~Player() {
    for (auto terr : ownedTerritories)  {
         delete terr;
         terr = NULL;
    } 
    ownedTerritories.clear();
    for (auto cards : handOfCards) {
        delete cards;
        cards = NULL;
    }  
    handOfCards.clear();
    for (auto orders : listOfOrders) {
        delete orders;
        orders = NULL;
    }
    listOfOrders.clear();
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& out, const Player& toOutput) {
    out << "Player has " << toOutput.ownedTerritories.size() << " territories, " 
    << toOutput.handOfCards.size() << " cards and " 
    << toOutput.listOfOrders.size() << " orders ready.";
    return out;
}

// Returns a vector of pointers of territories to defend
std::vector<Territory*> Player::toDefend() {
    return ownedTerritories;
}

// Returns a vector of pointers of territories to attack
std::vector<Territory*> Player::toAttack(Graph& graph) {
    std::vector<Territory*>* ptrVectorAllTerritories = graph.GetTerritories();
    std::vector<Territory*> territoriesToAttack;

    for (int i = 0; i < ptrVectorAllTerritories->size(); i++) {
        for (int j = 0; j < ownedTerritories.size(); j++) {
            // ownedTerritories is a vector of pointers, so to get the name of the territory, 
            // we dereference ownedTerritories[i] by using ->. We get the address of the name, 
            // but we want the actual name, thus using * before the whole (ownedTerritories[i]->GetName()).
            // prtVectorAllTerritories is a pointer to a vector, so to get the actual vector, 
            // we dereference it using *. To get the name, we dereference (*prtVectorAllTerritories)[j] 
            // by using ->. We have the address of the name, but to get the real name, we use *
            // before the whole (*ptrVectorAllTerritories)[i]->GetName().
            if (*(ownedTerritories[j]->GetName()) != (*(*ptrVectorAllTerritories)[i]->GetName()))
                territoriesToAttack.push_back((*ptrVectorAllTerritories)[i]);
        }
    }
    return territoriesToAttack;
}

// Creates an Order object and adds it to the vector of pointers of orders
void Player::issueOrder() {
    // Creating a Deploy order
    Order* orderToIssue = new Deploy();
    AddOrderToPlayer(orderToIssue);
}

// Adds the given territory pointer to the vector of owned territories
void Player::AddTerritoryToPlayer(Territory* territoryToAdd) {
    ownedTerritories.push_back(territoryToAdd);
}
// Adds the given card pointer to the vector of cards
void Player::AddCardToPlayer(Card* cardToAdd) {
    handOfCards.push_back(cardToAdd);
}
// Adds the given order pointer to the vector of orders
void Player::AddOrderToPlayer(Order* orderToAdd) {
    listOfOrders.push_back(orderToAdd);
}