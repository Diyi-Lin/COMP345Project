#include "Map.h"

Graph::Graph(int size) { this->territories.reserve(size); }
void Graph::AddTerritory(Territory* territory) { this->territories.push_back(territory); }
std::vector<Territory*> Graph::GetTerritories() { return this->territories; }

Territory::Territory(std::string name) { this->name = name; troops = 0; }
std::string Territory::GetName() { return this->name; }
void Territory::SetPlayer(Player* player) { this->player = player; }
Player* Territory::GetPlayer() { return this->player; }
void Territory::IncreaseTroops(int increase) { this->troops += increase; }
void Territory::DecraseTroops(int decrease) { this->troops -= decrease; }
int Territory::GetTroops() { return this->troops; }
void Territory::AddNeighbor(Territory* neighbor) { this->neighbors.push_back(neighbor); }  // TODO: check if this can be done more efficiently.
std::vector<Territory*> Territory::GetNeighbors() { return this->neighbors; }

void Graph::Visit(int index, std::vector<std::vector<int>> edges, std::vector<bool>* visited) {
  std::cout << "Visiting vertex at index: " << index << std::endl;
  visited->at(index) = true;
  for (int i = 0; i < edges.at(index).size(); i++) { // for each neighbor of territory at index
    int neighborIndex = edges.at(index).at(i);
    std::cout << "Neighbor found: " << neighborIndex << " : "
              << this->GetTerritories().at(neighborIndex)->GetName() << std::endl;
    if (visited->at(neighborIndex) == false) {  // If the neighbor hasn't been visited
      this->Visit(neighborIndex, edges, visited);  // visit the neighbor
    }
  }
}

bool Graph::DFS(std::vector<std::vector<int>> edges) {
  std::vector<bool> visited = std::vector<bool>(edges.size(), false);
  std::cout << "DFS" << std::endl;
  this->Visit(0, edges, &visited);
  if (std::find(visited.begin(), visited.end(), false) != visited.end()) {
    std::cout << "This graph is not strongly connected." << std::endl;
    return false;
  }
  return true;
}

bool Map::Validate() {
  std::cout << "Validating Map..."<< std::endl;
  std::vector<Territory*> terrs = this->GetTerritories();
  int size = terrs.size();
  if (size < 1) {
    std::cout << "This map does not contain any territory." << std::endl;
    return false;
  }
  Territory* front = terrs.front();
  std::vector<std::vector<int>> edges = std::vector<std::vector<int>>(size);
  std::vector<std::vector<int>> iedges = std::vector<std::vector<int>>(size);
  for (int i = 0; i < size; i++) { // For each territory
    Territory* t = terrs.at(i);
    edges.at(i) = std::vector<int>(t->GetNeighbors().size());
    for (int j = 0; j < t->GetNeighbors().size(); j++) { // For each neighbor
      int neighborIndex = t->GetNeighbors().at(j) - front;
      edges.at(i).at(j) = neighborIndex;
      iedges.at(neighborIndex).push_back(i);
    }
  }

  if (!DFS(edges)) {
    return false;
  }
  if (!DFS(iedges)) {
    return false;
  }
	
	std::cout << "This map is valid." << std::endl;
	return true;
}
Map::Map(int size, std::vector<Continent*> continents) : Graph(size) {
  this->continents = continents;
}
std::vector<Continent*> Map::GetContinents(){ return this->continents; }

Continent::Continent(int size, std::string name) : Graph(size) { this->name = name; }
void Continent::SetName(std::string name) { this->name = name; }
std::string Continent::GetName() { return this->name; }