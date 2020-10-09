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

class Graph {
 private:
  std::vector<Territory*> territories;
 public:
  Graph(int size);
  void AddTerritory(Territory* territory);
  std::vector<Territory*> GetTerritories();
  void Visit(int v, std::vector<std::vector<int>> edges,
             std::vector<bool>* visited);
  bool DFS(std::vector<std::vector<int>> edges);
};

class Continent : public Graph {
 private:
  std::string name;
 public:
  Continent(int size, std::string name);
  void SetName(std::string name);
  std::string GetName();
};

class Map : public Graph {
 private:
  std::vector<Continent*> continents;
 public:
  Map(int size, std::vector<Continent*> continents);
  std::vector<Continent*> GetContinents();
  bool Validate();
};

class Territory {
 private:
  std::string name;
  Player* player;
  int troops;
  std::vector<Territory*> neighbors;

 public:
  Territory(std::string name);
  std::string GetName();
  void SetPlayer(Player* player);
  Player* GetPlayer();
  void IncreaseTroops(int increase);
  void DecraseTroops(int decrease);
  int GetTroops();
  void AddNeighbor(Territory* neighbor);
  std::vector<Territory*> GetNeighbors();
};