#include "Orders.h"

#include <algorithm>

// Orders List
OrdersList::OrdersList() : ordersList() {}

OrdersList::OrdersList(const OrdersList& toCopy) : ordersList() {
  for (Order* o : *toCopy.ordersList) {
    // TODO create a copy of each Order
    // Must take subtype into account
  }
}

OrdersList::~OrdersList() {
  for (auto o : *ordersList) {
    delete o;
  }
  ordersList->clear();
  delete ordersList;
  ordersList = NULL;
}

OrdersList& OrdersList::operator=(const OrdersList& rightSide) {
  ordersList = rightSide.ordersList;
  return *this;
}

std::ostream& operator<<(std::ostream& outs, const OrdersList& toOutput) {
  outs << "Orders list with " << toOutput.ordersList->size() << " orders\n";
  return outs;
}

void OrdersList::queue(Order* order) { ordersList->push_back(order); }

void OrdersList::move(int orderPosition, int newOrderPosition) {
  orderPosition += 1;
  newOrderPosition += 1;
}

void OrdersList::remove(int position) { position += 1; }

// Orders
Order::Order() : player() {}

Order::Order(Player* player) { this->player = player; }

Order::Order(const Order& toCopy) {
  player = toCopy.player;
  wasExecuted = toCopy.wasExecuted;
}

Order& Order::operator=(const Order& rightSide) {
  player = rightSide.player;
  wasExecuted = rightSide.wasExecuted;
  return *this;
}

bool Order::areAdjacent(Territory* source, Territory* target) {
  std::vector<Territory*>* neighborsOfSource = source->GetNeighbors();
  return std::any_of(neighborsOfSource->begin(), neighborsOfSource->end(),
                     [target](Territory* t) { return (t == target); });
}

Deploy::Deploy() : Order(), territoryToDeploy() {}

Deploy::Deploy(Player* player, Territory* territory) : Order(player) {
  this->player = player;
  this->territoryToDeploy = territory;
}

Deploy::Deploy(const Deploy& toCopy) : Order(toCopy) {
  this->territoryToDeploy = toCopy.territoryToDeploy;
}

Deploy& Deploy::operator=(const Deploy& rightSide) {
  Order::operator=(rightSide);
  territoryToDeploy = rightSide.territoryToDeploy;
  return *this;
}

Deploy::~Deploy() {}

bool Deploy::validate() { return (territoryToDeploy->GetPlayer() == player); }

void Deploy::execute() {
  if (!validate()) {
    return;
  }
  wasExecuted = true;
  std::cout << "Deploying armies into some territory.\n";
}

Advance::Advance() : Order(), sourceTerritory(), targetTerritory() {}

Advance::Advance(Player* player, Territory* sourceTerritory,
                 Territory* targetTerritory)
    : Order(player) {
  this->sourceTerritory = sourceTerritory;
  this->targetTerritory = targetTerritory;
}
Advance::Advance(const Advance& toCopy) : Order(toCopy) {
  this->sourceTerritory = toCopy.sourceTerritory;
  this->targetTerritory = toCopy.targetTerritory;
}

Advance::~Advance() {}

Advance& Advance::operator=(const Advance& rightSide) {
  Order::operator=(rightSide);
  sourceTerritory = rightSide.sourceTerritory;
  targetTerritory = rightSide.targetTerritory;
  return *this;
}

bool Advance::validate() {
  // Check if source and target territories are neighbors
  return Order::areAdjacent(sourceTerritory, targetTerritory);
}

void Advance::execute() {
  if (!validate()) {
    return;
  }
  wasExecuted = true;
  std::cout << "Advancing into another territory.\n";
}

Bomb::Bomb() : Order(), sourceTerritory(), targetTerritory() {}

Bomb::Bomb(Player* player, Territory* sourceTerritory,
           Territory* targetTerritory)
    : Order(player) {
  this->sourceTerritory = sourceTerritory;
  this->targetTerritory = targetTerritory;
}

Bomb::Bomb(const Bomb& toCopy) : Order(toCopy) {
  this->sourceTerritory = toCopy.sourceTerritory;
  this->targetTerritory = toCopy.targetTerritory;
}

Bomb::~Bomb() {}

Bomb& Bomb::operator=(const Bomb& rightSide) {
  Order::operator=(rightSide);
  sourceTerritory = rightSide.sourceTerritory;
  targetTerritory = rightSide.targetTerritory;
  return *this;
}

bool Bomb::validate() {
  // Check that territories are adjacent and that target
  // does not belong to player
  bool areAdjacent = Order::areAdjacent(sourceTerritory, targetTerritory);
  bool targetDoesntBelongToPlayer = (targetTerritory->GetPlayer() != player);
  return (areAdjacent && targetDoesntBelongToPlayer);
}

void Bomb::execute() {
  if (!validate()) {
    return;
  }
  wasExecuted = true;
  std::cout << "Bombing an adjacent territory.\n";
}

Blockade::Blockade() : Order(), territoryToBlockade() {}

Blockade::Blockade(Player* player, Territory* territoryToBlockade)
    : Order(player) {
  this->territoryToBlockade = territoryToBlockade;
}

Blockade::Blockade(const Blockade& toCopy) : Order(toCopy) {
  this->territoryToBlockade = toCopy.territoryToBlockade;
}

Blockade::~Blockade() {}

Blockade& Blockade::operator=(const Blockade& rightSide) {
  Order::operator=(rightSide);
  territoryToBlockade = rightSide.territoryToBlockade;
  return *this;
}

bool Blockade::validate() {
  // Check that the territory belongs to player
  return (territoryToBlockade->GetPlayer() == player);
}

void Blockade::execute() {
  if (!validate()) {
    return;
  }
  wasExecuted = true;
  std::cout << "Blockading a territory.\n";
}

Negotiate::Negotiate() : Order(), opponent() {}

Negotiate::Negotiate(Player* player, Player* opponent) : Order(player) {
  this->opponent = opponent;
}

Negotiate::Negotiate(const Negotiate& toCopy) : Order(toCopy) {
  this->opponent = toCopy.opponent;
}

Negotiate::~Negotiate() {}

Negotiate& Negotiate::operator=(const Negotiate& rightSide) {
  Order::operator=(rightSide);
  opponent = rightSide.opponent;
  return *this;
}

bool Negotiate::validate() {
  // Check that the players negotiating aren't the same
  return player != opponent;
}

void Negotiate::execute() {
  if (!validate()) {
    return;
  }
  wasExecuted = true;
  std::cout << "A peace deal was striken.\n";
}

Airlift::Airlift() : Order(), sourceTerritory(), targetTerritory() {}

Airlift::Airlift(Player* player, Territory* sourceTerritory,
                 Territory* targetTerritory)
    : Order(player) {
  this->sourceTerritory = sourceTerritory;
  this->targetTerritory = targetTerritory;
}

Airlift::Airlift(const Airlift& toCopy) : Order(toCopy) {
  this->sourceTerritory = toCopy.sourceTerritory;
  this->targetTerritory = toCopy.targetTerritory;
}

Airlift::~Airlift() {}

Airlift& Airlift::operator=(const Airlift& rightSide) {
  Order::operator=(rightSide);
  sourceTerritory = rightSide.sourceTerritory;
  targetTerritory = rightSide.targetTerritory;
  return *this;
}

bool Airlift::validate() {
  // Not really sure how to validate this order
  // Checks if the territories are defined for now
  return (sourceTerritory->GetPlayer() == player && targetTerritory != NULL);
}

void Airlift::execute() {
  if (!validate()) {
    return;
  }
  wasExecuted = true;
  std::cout << "Airlifting into another territory!\n";
}
