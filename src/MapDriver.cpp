#define MAP_DRIVER
#ifdef MAP_DRIVER

#include <iostream>
#include <string>

#include "Map.h"

int main() {
  Territory territories[4] = {
      Territory(std::string("T0")), Territory(std::string("T1")),
      Territory(std::string("T2")), Territory(std::string("T3"))};
  territories[0].AddNeighbor(&territories[1]);
  territories[1].AddNeighbor(&territories[2]);
  territories[2].AddNeighbor(&territories[3]);
  territories[0].AddNeighbor(&territories[3]);
  territories[3].AddNeighbor(&territories[0]);
  std::vector<Continent*> continents = std::vector<Continent*>();
  Map map = Map(4, continents);
  map.AddTerritory(&territories[0]);
  map.AddTerritory(&territories[1]);
  map.AddTerritory(&territories[2]);
  map.AddTerritory(&territories[3]);
  map.Validate();
}

#endif