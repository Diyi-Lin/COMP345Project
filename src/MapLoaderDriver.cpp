#include "MapLoader.h"

//#define MAP_LOADER_DRIVER
#ifdef MAP_LOADER_DRIVER

  int main() {
  //Create a new map loader
  MapLoader* ml = new MapLoader();
  std::cout << (*ml);
  std::string input;
  std::cout
      << "Please Enter the name of the map file that is to be created. \n";
  //Generate the map
  std::cin >> input;
  Map* map = ml->GenerateMap("MapFiles/"+input);
  //The ml being deleted should not affect the persistance of the created map
  delete ml;
  
  for (int i = 0; i < map->GetContinents().size();++i) {
    Continent* continent = map->GetContinents()[i];
    std::cout << continent->GetName() << std::endl;
    for (int j = 0; j<continent->GetTerritories()->size();++j) {
      Territory* territory =(*map->GetTerritories())[j];
      std::cout << *territory->GetName() << " Neighbors: ";
      for (int k = 0; k < territory->GetNeighbors()->size();++k) {
        int index = (*territory->GetNeighbors())[k];
        Territory* neb = (*map->GetTerritories())[index];
        std::cout << "  " << *neb->GetName();
      }
      std::cout << std::endl;
    }
    std::cout << "*****************************************************"
              << std::endl;
    std::cout << std::endl;
  }

  
  return 0;


}
#endif
