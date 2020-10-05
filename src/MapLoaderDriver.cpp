#include "MapLoader.h"

//#define MAP_LOADER_DRIVER
#ifdef MAP_LOADER_DRIVER
int main() {
  //Create a new map loader
  MapLoader* ml = new MapLoader();
  std::string input;
  std::cout
      << "Please Enter the name of the map file that is to be created. \n";
  //Generate the map
  std::cin >> input;
  Map* map = ml->GenerateMap("MapFiles/"+input);
  //The ml being deleted should not affect the persistance of the created map
  delete ml;
  //Display the map information
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
