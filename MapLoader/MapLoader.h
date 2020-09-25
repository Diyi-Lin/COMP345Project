#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>
using namespace std;

class Continent;
class Territory
{
public:
	string name;
	Continent* continent;
	vector<Territory*> neighbors;
};
class Continent
{
public:
	string name;
	int armyValue;
	vector<Territory*> territories;
};
class Map
{
public:
	vector<Territory*> territories;
	vector<Continent*> continents;
	void print()
	{
		for (auto x : continents)
		{
			cout << "Continent: " << x->name << endl;
			for (auto y : x->territories)
			{
				cout << "Territory: " << y->name << endl;
				for (auto z : y->neighbors)
					cout << " Neighbor " << z->name;
				cout << endl;
			}
			cout << "---------------------------------" << endl;
			cout << endl;
		}
	}
};



class MapLoader
{

public:
	MapLoader();
	~MapLoader();
	Map* GenerateMap(string filePath);

private:

	struct ValidityData
	{
		bool filesFound = false;
		bool continentsFound = false;
		bool territoriesFound = false;
		bool bordersFound = false;
		bool validData = true;

		inline bool IsValid()
		{
			return filesFound && continentsFound && territoriesFound && bordersFound && validData;
		}
	};

	enum DataType
	{
		Continents = 0,
		Territories,
		Borders,
		None
	};
	
	Map* generatedMap;
	map<int, Territory*>* territoriesMap;
	map<int, Continent*>* continentsMap;
	int countinentsCount;
	ValidityData* validityData;
	vector<string> Split(string line) const;
	void ProcessContinents(string line, DataType* dataType);
	void ProcessTerritories(string line, DataType* dataType);
	void ProcessBorders(string line, DataType* dataType);
	void ReadFile(string path);

};

