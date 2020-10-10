// COMP 345 - Project
// Part 1
// Jordan Goulet - 40075688
// FirstName LastName - 00000000
// FirstName LastName - 00000000
// FirstName LastName - 00000000
// FirstName LastName - 00000000
// 
// Based on the 'https://www.warzone.com/' game.

#pragma once

#include <string>
#include <vector>

#include "Player.h"

class Territory;
class Player;

class Continent{
 private:
  std::string name;
  std::vector<Territory> territories;
  int bonus;
 public:
  Continent(std::string name, int bonus);
  std::string GetName();
  std::vector<Territory>* GetTerritories();
  void CreateTerritory(int id, std::string name);
  int GetBonus();
};

class Map {
 private:
  std::vector<std::vector<int>> borders;
  std::vector<Continent*> continents;
 public:
  Map(int vertices, int continents);
  void AddContinent(Continent* continent);
  std::vector<Continent*> GetContinents();
  void AddBorder(std::vector<int> data);
  bool AreAdjacent(Territory* source, Territory* target);
  std::vector<Territory*> GetTerritories();
  std::vector<Territory*> GetNeighbors(Territory* territory);
  Territory* GetTerriotryByID(int id);
  std::vector<std::vector<int>>* GetBorders();
  std::vector<int>* GetBordersById(int id);
  void Visit(int id);
  bool Validate();
};

class Territory {
 private:
  std::string name;
  int id;
  Player* player;
  int troops;
  bool visited = false;

 public:
  Territory();
  Territory(int id, std::string name);
  std::string* GetName();
  void SetPlayer(Player* player);
  Player* GetPlayer();
  void SetId(int id);
  int GetId();
  void IncreaseTroops(int increase);
  void DecraseTroops(int decrease);
  int GetTroops();
  void SetVisited(bool b);
  bool GetVisited();
};