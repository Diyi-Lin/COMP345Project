#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Map.h"
#include "Player.h"

class Order {
 public:
  Order();
  Order(Player* player);
  Order(const Order& toCopy);
  virtual ~Order();
  Order& operator=(const Order& rightSide);

  virtual bool validate() = 0;
  virtual void execute() = 0;

  friend std::ostream& operator<<(std::ostream& out, const Order& toOutput);

  // Helper function to know if two territories are adjacent
  // Put this here atm but should probably be moved to map functionnalities
  static bool areAdjacent(Territory* source, Territory* target);

 protected:
  Player* player;
  bool wasExecuted{false};
};

// Deploy armies to one of player's territories
class Deploy : public Order {
 public:
  Deploy();
  Deploy(Player* player, Territory* territory);
  Deploy(const Deploy& toCopy);
  ~Deploy();
  Deploy& operator=(const Deploy& rightSide);

  friend std::ostream& operator<<(std::ostream& out, const Deploy& toOutput);

  virtual bool validate();
  virtual void execute();

 private:
  Territory* territoryToDeploy;
};

// Advance armies from source to target territories, attacking if needed
class Advance : public Order {
 public:
  Advance();
  Advance(Player* player, Territory* sourceTerritory,
          Territory* targetTerritory);
  Advance(const Advance& toCopy);
  ~Advance();
  Advance& operator=(const Advance& rightSide);

  friend std::ostream& operator<<(std::ostream& out, const Advance& toOutput);

  virtual bool validate();
  virtual void execute();

 private:
  Territory* sourceTerritory;
  Territory* targetTerritory;
};

// Bomb an opponent's adjacent territory
class Bomb : public Order {
 public:
  Bomb();
  Bomb(Player* player, Territory* sourceTerritory, Territory* targetTerritory);
  Bomb(const Bomb& toCopy);
  ~Bomb();
  Bomb& operator=(const Bomb& rightSide);

  friend std::ostream& operator<<(std::ostream& out, const Bomb& toOutput);

  virtual bool validate();
  virtual void execute();

 private:
  Territory* sourceTerritory;
  Territory* targetTerritory;
};

// Triple armies on one of player's territories, making it neutral
class Blockade : public Order {
 public:
  Blockade();
  Blockade(Player* player, Territory* territoryToBlockade);
  Blockade(const Blockade& toCopy);
  ~Blockade();
  Blockade& operator=(const Blockade& rightSide);

  friend std::ostream& operator<<(std::ostream& out, const Blockade& toOutput);

  virtual bool validate();
  virtual void execute();

 private:
  Territory* territoryToBlockade;
};

// Negotiate peace for a turn between player and opponent
class Negotiate : public Order {
 public:
  Negotiate();
  Negotiate(Player* player, Player* opponent);
  Negotiate(const Negotiate& toCopy);
  ~Negotiate();
  Negotiate& operator=(const Negotiate& rightSide);

  friend std::ostream& operator<<(std::ostream& out, const Negotiate& toOutput);

  virtual bool validate();
  virtual void execute();

 private:
  Player* opponent;
};

// Advance armies from a player's territory to any territory
class Airlift : public Order {
 public:
  Airlift();
  Airlift(Player* player, Territory* sourceTerritory,
          Territory* targetTerritory);
  Airlift(const Airlift& toCopy);
  ~Airlift();
  Airlift& operator=(const Airlift& rightSide);

  friend std::ostream& operator<<(std::ostream& out, const Airlift& toOutput);

  virtual bool validate();
  virtual void execute();

 private:
  Territory* sourceTerritory;
  Territory* targetTerritory;
};

class OrdersList {
 public:
  OrdersList();
  OrdersList(const OrdersList& toCopy);
  ~OrdersList();
  OrdersList& operator=(const OrdersList& rightSide);

  // Add an order to the end of the orders list
  void queue(Order* o);

  // Takes order at position orderPosition and moves it at newOrderPosition,
  // shifting other orders accordingly Position" is 1-indexed instead of
  // 0-indexed (more intuitive to the player)
  void move(int orderPosition, int newOrderPosition);

  // Removes the order at position (i.e. 1-indexed) in the list
  // Method is called remove instead of delete b/c delete is a
  // reserved keyword, which drove Visual Studio nuts
  void remove(int position);

  friend std::ostream& operator<<(std::ostream& outs,
                                  const OrdersList& toOutput);

 private:
  std::vector<Order*>* ordersList;
};
