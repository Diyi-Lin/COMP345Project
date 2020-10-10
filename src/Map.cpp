#include "Map.h"

Continent::Continent(std::string name, int bonus) {
  this->territories = std::vector<Territory>();
  this->name = name;
  this->bonus = bonus;
}
std::string Continent::GetName() { return this->name; }
std::vector<Territory>* Continent::GetTerritories() { return &this->territories; }
void Continent::CreateTerritory(int id, std::string name) {
  this->territories.push_back(Territory(id, name));
}
int Continent::GetBonus() { return this->bonus; }

Map::Map(int vertices, int continents) {
  this->continents.reserve(continents);
  this->borders.reserve(vertices);
}
void Map::AddContinent(Continent* continent) { this->continents.push_back(continent); }
std::vector<Continent*> Map::GetContinents() { return this->continents; }
void Map::AddBorder(std::vector<int> data) { this->borders.push_back(data); }
bool Map::AreAdjacent(Territory* source, Territory* target) {
  int sourceId = source->GetId();
  int targetId = target->GetId();
  for (std::vector<int> t : this->borders) {
    if (t.at(0) == sourceId) {
      if (std::find(t.begin(), t.end(), targetId) != t.end()) {
        return true;
      }
      return false;
    }
  }
}
std::vector<Territory*> Map::GetTerritories() { 
  int size = 0;
  for (Continent* c : this->continents) {
    size += c->GetTerritories()->size();
  }
  std::vector<Territory*> terrs = std::vector<Territory*>(size);
  for (Continent* c : this->continents) {
    for (int i = 0; i < c->GetTerritories()->size(); i++) {
      terrs.push_back(&c->GetTerritories()->at(i));
    }
  }
  return terrs;
}
Territory* Map::GetTerriotryByID(int id) {
  for (Continent* c : this->continents) {
    for (int i = 0; i < c->GetTerritories()->size(); i++) {
      if (c->GetTerritories()->at(i).GetId() == id) {
        return &c->GetTerritories()->at(i);
      }
    }
  }
}
// This algorithm has high complexity, use at own risk!
std::vector<Territory*> Map::GetNeighbors(Territory* territory) {
  std::vector<Territory*> terrs;
  int id = territory->GetId();
  for (std::vector<int> t : this->borders) {
    if (t.at(0) == id) {
      for (int i = 1; i < t.size(); i++) {
        terrs.push_back(this->GetTerriotryByID(t.at(i)));
      }
      return terrs;
    }
  }
}
std::vector<std::vector<int>>* Map::GetBorders() { return &this->borders; }
std::vector<int>* Map::GetBordersById(int id) {
  for (std::vector<int>& t : this->borders) {
    if (t.at(0) == id) {
      return &t;
    }
  }
}
void Map::Visit(int id) {
  Territory* territory = this->GetTerriotryByID(id);
  std::cout << "Visiting: " << id << " : " << *territory->GetName() << std::endl;
  if (territory->GetVisited() == true) {
    std::cout << "Its already visited" << std::endl;
    return;
  }
  territory->SetVisited(true);
  std::vector<int>* borders = this->GetBordersById(id);
  std::cout << "This terr has this many border: " << borders->size()
            << std::endl;
  for (int i = 1; i < borders->size(); i++) {
    std::cout << "Border: " << borders->at(i) << std::endl;
    this->Visit(borders->at(i));
  }
}
bool Map::Validate() { 
    std::cout << "Validating..." << std::endl;
    std::vector<std::vector<int>>* borders = &this->borders;
    if (this->continents.size() < 1) {
      std::cout << "Map doesnt have continents." << std::endl;
      return false;
    }
    for (Continent* c : this->continents) {
      std::cout << "Continent: " << c->GetName() << std::endl;
      std::vector<Territory>* terrs = c->GetTerritories();
      if (terrs->size() < 1) {
        std::cout << "Continent doesnt have territories" << std::endl;
        return false;
      }
      for (int i = 0; i < terrs->size(); i++) {
        terrs->at(i).SetVisited(false);
      }
    }
    std::cout << "Starting visits" << std::endl;
    this->Visit(this->continents.at(0)->GetTerritories()->at(0).GetId());
    std::cout << "Ended visits" << std::endl;
    for (Continent* c : this->continents) {
      std::vector<Territory>* terrs = c->GetTerritories();
      for (int i = 0; i < terrs->size(); i++) {
        if (terrs->at(i).GetVisited() == false) {
          return false;
        }
        terrs->at(i).SetVisited(false);
      }
    }
    std::vector<std::vector<int>> iborders;
    iborders.reserve(borders->size());
    for (Continent* c : this->continents) {
      std::vector<Territory>* terrs = c->GetTerritories();
      for (int i = 0; i < terrs->size(); i++) {
        std::vector<int> b = {terrs->at(i).GetId()};
        iborders.push_back(b);
      }
    }
    /*for (int i = 0; i < borders->size(); i++) {
      int id = borders->at(i).at(0);
      for (int j = 1; j < borders->at(i).size(); i++) {
        std::vector<int> a = std::find(borders->begin(), borders->end(), j);
        if 
        a.push_back(id[0]);
      }
    }*/
    return true;
}


Territory::Territory() : id(0), name(), player(), troops(0) {} // TODO ?

Territory::Territory(int id, std::string name) {
  this->id = id;
  this->name = name;
}
std::string* Territory::GetName() {
  return &this->name;
}
void Territory::SetPlayer(Player* player) {
  this->player = player;}
Player* Territory::GetPlayer() {
  return this->player;}
void Territory::SetId(int id) {
  this->id = id;}
int Territory::GetId() {
  return this->id;}
void Territory::IncreaseTroops(int increase) {
  this->troops += increase;}
void Territory::DecraseTroops(int decrease) {
  this->troops -= decrease;}
int Territory::GetTroops() {
  return this->troops;}
void Territory::SetVisited(bool b) {
  this->visited = b;}
bool Territory::GetVisited() {
  return this->visited;}
