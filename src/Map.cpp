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
bool Continent::AreAllVisited() {
  for (Territory &t : this->territories) {
    if (!t.GetVisited()) {
      return false;
    }
  }
  return true;
}

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
std::vector<int>* Map::GetBordersById(int id,
                                      std::vector<std::vector<int>>* borders) {
  for (int i = 0; i < borders->size(); i++) {
    if (borders->at(i).at(0) == id) {
      return &borders->at(i);
    }
  }
  return nullptr;
}
void Map::Visit(int id, std::vector<std::vector<int>>* borders) {
  Territory* territory = this->GetTerriotryByID(id);
  if (territory->GetVisited() == true) {
    return;
  }
  territory->SetVisited(true);
  std::vector<int>* border = this->GetBordersById(id, borders);
  if (border == nullptr) return;
  for (int i = 1; i < border->size(); i++) {
    this->Visit(border->at(i), borders);
  }
}
std::vector<std::vector<int>> Map::GetInvertedBorders() {
  std::vector<std::vector<int>>* borders = &this->borders;
  std::vector<std::vector<int>> iborders;
  iborders.reserve(borders->size());
  for (Continent* c : this->continents) {
    std::vector<Territory>* terrs = c->GetTerritories();
    for (int i = 0; i < terrs->size(); i++) {
      iborders.push_back({terrs->at(i).GetId()});
    }
  }
  for (int i = 0; i < borders->size(); i++) {
    int v = borders->at(i).at(0);
    for (int j = 1; j < borders->at(i).size(); j++) {
      int u = borders->at(i).at(j);
      this->GetBordersById(u, &iborders)->push_back(v);
    }
  }
  return iborders;
}
std::vector<std::vector<int>> Map::GetContinentBorders(
    Continent* continent, std::vector<std::vector<int>>* borders) {
  std::vector<std::vector<int>> cborders;
  cborders.reserve(continent->GetTerritories()->size());
  for (int i = 0; i < continent->GetTerritories()->size(); i++) {
    cborders.push_back({continent->GetTerritories()->at(i).GetId()});
  }
  for (std::vector<int> &b : cborders) {
    std::vector<int>* border = GetBordersById(b.at(0), borders);
    if (border == nullptr) continue;
    for (int i = 1; i < border->size(); i++) {
      int id = border->at(i);
      for (int j = 0; j < cborders.size(); j++) {
        if (cborders.at(j).at(0) == id) {
          b.push_back(id);
        }
      }
    }
  } 
  return cborders;
}
void Map::AllSetVisited(bool b) {
  for (Continent* c : this->continents) {
    std::vector<Territory>* terrs = c->GetTerritories();
    for (int i = 0; i < terrs->size(); i++) {
      terrs->at(i).SetVisited(b);
    }
  }
}
bool Map::AreAllVisited() {
  for (Continent* c : this->continents) {
    std::vector<Territory>* terrs = c->GetTerritories();
    for (int i = 0; i < terrs->size(); i++) {
      if (terrs->at(i).GetVisited() == false) {
        return false;
      }
      terrs->at(i).SetVisited(false);
    }
  }
  return true;
}

bool Map::Validate() { 
  std::vector<std::vector<int>>* borders = &this->borders;
  std::vector<std::vector<int>> iborders = this->GetInvertedBorders();
  this->AllSetVisited(false);

  if (this->continents.size() < 1) { // Empty maps are valid.
    return true;
  }
  int id = -1;
  for (int i = 0; i < this->GetContinents().size(); i++) {
    if (this->GetContinents().at(i)->GetTerritories()->size() > 0) {
      id = i;
      break;
    }
  }
  if (id == -1) { // All continents are empty
    return true;
  }

  try {
    this->Visit(this->continents.at(id)->GetTerritories()->at(0).GetId(), borders);
  } catch (...) {
    std::cout << "************Error: unable to traverse." << std::endl;
    return false;
  }
  if (!this->AreAllVisited()) {
    return false;
  }
  this->AllSetVisited(false);

  try {
    this->Visit(this->continents.at(id)->GetTerritories()->at(0).GetId(),
                &iborders);
  } catch (...) {
    std::cout << "************Error: unable to traverse." << std::endl;
    return false;
  }
  if (!this->AreAllVisited()) {
    return false;
  }
  this->AllSetVisited(false);

  std::vector<std::vector<int>> cborders;
  std::vector<std::vector<int>> icborders;

  for (Continent* c : this->continents) {
    cborders = this->GetContinentBorders(c, borders);
    if (c->GetTerritories()->size() < 1) {
      continue;
    }
    try {
      this->Visit(c->GetTerritories()->at(0).GetId(),
                  &cborders);
    } catch (...) {
      std::cout << "************Error: unable to traverse." << std::endl;
      return false;
    }
    if (!c->AreAllVisited()) {
      return false;
    }
    this->AllSetVisited(false);

    icborders = this->GetContinentBorders(c, &iborders);
    try {
      this->Visit(c->GetTerritories()->at(0).GetId(), &icborders);
    } catch (...) {
      std::cout << "************Error: unable to traverse." << std::endl;
      return false;
    }
    if (!c->AreAllVisited()) {
      return false;
    }
    this->AllSetVisited(false);
  }

  for (Continent* c : this->continents) {
    std::vector<Territory>* terrs = c->GetTerritories(); 
    for (int i = 0; i < terrs->size(); i++) {
      Territory* t = &terrs->at(i);
      if (t->GetVisited() == true) {
        return false;
      }
      t->SetVisited(true);
    }
  }
  if (!this->AreAllVisited()) {
    return false;
  }

  this->AllSetVisited(false);
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
