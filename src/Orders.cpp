#include "Orders.h"

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
  // TODO: insert return statement here
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

Order& Order::operator=(const Order& rightSide) {
  // TODO: insert return statement here
  return *this;
}

Deploy::Deploy() : Order(), territoryToDeploy() {}

Deploy::Deploy(Player* player, Territory* territory) : Order(player) {
  this->player = player;
  this->territoryToDeploy = territory;
}

Deploy::Deploy(const Deploy& toCopy) {
  this->player = toCopy.player;
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
  std::cout << "Execute deploy\n";
}

Advance::Advance() : Order(), sourceTerritory(), targetTerritory() {}

Advance::Advance(Player* player, Territory* sourceTerritory,
                 Territory* targetTerritory)
    : Order(player) {
  this->sourceTerritory = sourceTerritory;
  this->targetTerritory = targetTerritory;
}
Advance::Advance(const Advance& toCopy) {}

Advance::~Advance() {}

Advance& Advance::operator=(const Advance& rightSide) {
  // TODO: insert return statement here
  return *this;
}

bool Advance::validate() { return true; }

void Advance::execute() {
  if (!validate()) {
    return;
  }
  wasExecuted = true;
  std::cout << "Execute advance\n";
}

Bomb::Bomb() : Order(), sourceTerritory(), targetTerritory() {}

Bomb::Bomb(Player* player, Territory* sourceTerritory,
           Territory* targetTerritory)
    : Order(player) {
  this->sourceTerritory = sourceTerritory;
  this->targetTerritory = targetTerritory;
}

Bomb::Bomb(const Bomb& toCopy) {}

Bomb::~Bomb() {}

bool Bomb::validate() { return true; }

void Bomb::execute() {
  if (!validate()) {
    return;
  }
  wasExecuted = true;
  std::cout << "Execute bomb\n";
}

Blockade::Blockade() : Order(), territoryToBlockade() {}

Blockade::Blockade(Player* player, Territory* territoryToBlockade)
    : Order(player) {
  this->territoryToBlockade = territoryToBlockade;
}

Blockade::Blockade(const Blockade& toCopy) {}

Blockade::~Blockade() {}

Blockade& Blockade::operator=(const Blockade& rightSide) {
  // TODO: insert return statement here
  return *this;
}

bool Blockade::validate() { return true; }

void Blockade::execute() {
  if (!validate()) {
    return;
  }
  wasExecuted = true;
  std::cout << "Execute blockade\n";
}

Negotiate::Negotiate() : Order(), opponent() {}

Negotiate::Negotiate(Player* player, Player* opponent) : Order(player) {
  this->opponent = opponent;
}

Negotiate::Negotiate(const Negotiate& toCopy) {}

Negotiate::~Negotiate() {}

Negotiate& Negotiate::operator=(const Negotiate& rightSide) {
  // TODO: insert return statement here
  return *this;
}

bool Negotiate::validate() { return true; }

void Negotiate::execute() {
  if (!validate()) {
    return;
  }
  wasExecuted = true;
  std::cout << "Execute negotiate\n";
}

Airlift::Airlift() : Order(), sourceTerritory(), targetTerritory() {}

Airlift::Airlift(Player* player, Territory* sourceTerritory,
                 Territory* targetTerritory)
    : Order(player) {
  this->sourceTerritory = sourceTerritory;
  this->targetTerritory = targetTerritory;
}

Airlift::Airlift(const Airlift& toCopy) {}

Airlift::~Airlift() {}

Airlift& Airlift::operator=(const Airlift& rightSide) {
  // TODO: insert return statement here
  return *this;
}

bool Airlift::validate() { return true; }

void Airlift::execute() {
  if (!validate()) {
    return;
  }
  wasExecuted = true;
  std::cout << "Execute airlift\n";
}
