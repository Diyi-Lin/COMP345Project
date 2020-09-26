#include "MapLoader.h"

#define MAP_LOADER_DRIVER
#ifdef MAP_LOADER_DRIVER
int main() {
  MapLoader* ml = new MapLoader();
  std::string input;

  Map* map = ml->GenerateMap("MapFiles/canada.map");
  delete ml;
  for (auto x : map->GetContinents()) {
    std::cout << x->GetName() << std::endl;
    for (auto y : *x->GetTerritories()) {
      std::cout << *y->GetName() <<  std::endl;
      std::cout <<"NEIGHBORS**: ";
      for (auto z : *y->GetNeighbors()) {
        std::cout << *z->GetName() << ", "; 
      }
      std::cout << std::endl;
    }
    std::cout << "-------------------------------------------------\n" << std::endl;
  }
  return 0;
}
#endif
