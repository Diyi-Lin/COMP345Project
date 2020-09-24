#include "MapLoader.h"


vector<string> MapLoader::split(string line) const
{
	vector<string> splitStrings;
	size_t prev{ 0 }, pos{ 0 };
	do
	{
		pos = line.find(' ', prev);
		if (pos == string::npos)
			pos = line.length();
		string split = line.substr(prev, pos - prev);
		if (!split.empty())
			splitStrings.push_back(split);
		prev = pos + 1;
	} while (pos < line.length() && prev < line.length());
	return splitStrings;
}

void MapLoader::processBorders(string line, DataType* dataType)
{
	vector<string> words = split(line);
	if (words.size() > 0)
	{
		if (words.size() < 2)
		{
			validityData->validData = false;
			cout << "Error, territory has no edges... invalid map file" << endl;
		}
		try {
			map<int, Territory*>::iterator it;
			it = territoriesMap->find(stoi(words[0]));
			Territory* territory;
			if (it != territoriesMap->end())
			{
				territory = it->second;
				for (int i = 1; i < words.size(); i++)
				{
					it = territoriesMap->find(stoi(words[i]));
					if (it != territoriesMap->end())
						territory->neighbors.push_back(it->second);
					else
					{
						validityData->validData = false;
						cout << "Iterator not found for territory: " << stoi(words[i]) << endl;
					}

				}
			}
			else
			{
				validityData->validData = false;
				cout << "Iterator not found for territory: " << words[0] << endl;
			}


		}
		catch (invalid_argument)
		{
			cout << "failure reading integer" << endl;
			validityData->validData = false;
		}
	}
	else
		*dataType = DataType::None;

}

void MapLoader::processContinents(string line, DataType* dataType)
{
	vector<string> words = split(line);
	Continent* continent = new Continent();
	if (words.size() > 0)
	{
		if (words.size() != 3)
			validityData->validData = false;
		continent->name = words[0];
		int index;
		try {
			continent->armyValue = stoi(words[1]);
		}
		catch (invalid_argument)
		{
			cout << "failure reading integer" << endl;
			validityData->validData = false;
		}
		generatedMap->continents.push_back(continent);
		continentsMap->insert(pair<int, Continent*>(generatedMap->continents.size(), continent));
	}
	else
		*dataType = DataType::None;
}

void MapLoader::processTerritories(string line, DataType* dataType)
{
	Territory* territory = new Territory();
	vector<string> words = split(line);
	if (words.size() > 0)
	{
		if (words.size() < 3)
			validityData->validData = false;
		territory->name = words[1];
		try {
			map<int, Continent*>::iterator it;
			it = continentsMap->find(stoi(words[2]));
			if (it != continentsMap->end())
				it->second->territories.push_back(territory);
			else
			{
				validityData->validData = false;
				cout << "Iterator not found for continent: " << stoi(words[2]) << endl;
			}


			generatedMap->territories.push_back(territory);
			territoriesMap->insert(pair<int, Territory*>(stoi(words[0]), territory));

		}
		catch (invalid_argument)
		{
			cout << "failure reading integer" << endl;
			validityData->validData = false;
		}
	}
	else
		*dataType = DataType::None;
}
void MapLoader::readFile(string path) {
	string line;
	ifstream myfile(path);
	DataType dataType = DataType::None;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			regex title("\\[[a-z]+\\]");
			smatch m;
			if (regex_search(line, m, title))
			{
				if (m.str().compare("[files]") == 0)
				{
					validityData->filesFound = true;
				}
				else if (m.str().compare("[continents]") == 0)
				{
					dataType = DataType::Continents;
					validityData->continentsFound = true;
				}
				else if (m.str().compare("[countries]") == 0)
				{
					dataType = DataType::Territories;
					validityData->territoriesFound = true;
				}
				else if (m.str().compare("[borders]") == 0)
				{
					dataType = DataType::Borders;
					validityData->bordersFound = true;
				}
			}
			else
			{
				switch (dataType)
				{
				case(DataType::Continents):
					processContinents(line, &dataType);
					break;
				case(DataType::Territories):
					processTerritories(line, &dataType);
					break;
				case(DataType::Borders):
					processBorders(line, &dataType);
					break;
				}
			}
		}
		myfile.close();
	}
	else
		cout << "Unable to open file";

}

Map* MapLoader::GenerateMap(string filePath)
{
	generatedMap = new Map();
	readFile(filePath);
	if (validityData->isValid())
		cout << "This is a valid map file" << endl;
	else
		cout << "This is not a valid map" << endl;
	return generatedMap;
}


MapLoader::MapLoader()
{
	validityData = new ValidityData();
	territoriesMap = new map<int, Territory*>();
	continentsMap = new map<int, Continent*>();
}


MapLoader::~MapLoader()
{
	delete validityData;
	delete territoriesMap;
	delete continentsMap;
}
