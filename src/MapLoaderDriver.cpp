// #define MAP_LOADER_DRIVER
#ifdef MAP_LOADER_DRIVER
#include "MapLoader.h"

int main()
{
	MapLoader* ml = new MapLoader();
	string input;
	cout << "Please enter a file name/path for a .map file to generate a map: ";
	cin >> input;
	Map* map = ml->GenerateMap(input);
	delete ml;
	map->print();
	//Map* map = ml.GenerateMap("canada.map");
	return 0;
}
#endif