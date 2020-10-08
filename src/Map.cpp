#include "Map.h"

Graph::Graph(int size) { this->territories.reserve(size); }
void Graph::AddTerritory(Territory* territory) { this->territories.push_back(territory); }
std::vector<Territory*>* Graph::GetTerritories() { return &this->territories; }

Territory::Territory(std::string* name) { this->name = name; troops = 0; }
std::string* Territory::GetName() { return this->name; }
void Territory::SetPlayer(Player* player) { this->player = player; }
Player* Territory::GetPlayer() { return this->player; }
void Territory::IncreaseTroops(int increase) { this->troops += increase; }
void Territory::DecraseTroops(int decrease) { this->troops -= decrease; }
int Territory::GetTroops() { return this->troops; }
void Territory::AddNeighbor(int id) { this->neighbors.push_back(id); }  // TODO: check if this can be done more efficiently.
std::vector<int>* Territory::GetNeighbors() { return &this->neighbors; }

bool Map::Validate() {
  std::vector<Territory*>* t = this->GetTerritories();
  std::vector<std::vector<int>> reverseAdjacency = std::vector<std::vector<int>>(t->size());
  for (int i = 0; i < t->size(); i++) {
    // in progress
  }
	return true;} // TODO
Map::Map(int size, std::vector<Continent*>* continents) : Graph(size) {
  this->continents = *continents;
  bool isValid = this->Validate();
}
std::vector<Continent*> Map::GetContinents(){ return this->continents; }

Continent::Continent(int size, std::string name) : Graph(size) { this->name = name; }
void Continent::SetName(std::string name) { this->name = name; }
std::string Continent::GetName() { return this->name; }