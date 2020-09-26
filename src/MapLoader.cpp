#include "MapLoader.h"

std::vector<std::string> MapLoader::Split(std::string line) const {
  std::vector<std::string> splitStrings;
  size_t prev{0}, pos{0};
  do {
    pos = line.find(' ', prev);
    if (pos == std::string::npos) pos = line.length();
    std::string split = line.substr(prev, pos - prev);
    if (!split.empty()) splitStrings.push_back(split);
    prev = pos + 1;
  } while (pos < line.length() && prev < line.length());
  return splitStrings;
}

void MapLoader::PreprocessContinents(std::string line, DataType* dataType) {
  std::vector<std::string> words = Split(line);
  if (words.size() > 0) {
    continentsCount++;
  } else {
    std::cout << "The continents count: " << continentsCount << std::endl;
    continentsSizes = new int[continentsCount];
    for (int i = 0; i < continentsCount; i++) continentsSizes[i] = 0;
    continents = std::vector<Continent*>();
    continents.reserve(continentsCount);
    *dataType = DataType::None;
  }
}

void MapLoader::PreprocessTerritories(std::string line, DataType* dataType) {
  std::vector<std::string> words = Split(line);
  if (words.size() > 0) {
    if (words.size() < 3) validityData->validData = false;
    territoriesCount++;
    try {
      int belongsTo = std::stoi(words[2]);
      continentsSizes[belongsTo - 1]++;

    } catch (std::invalid_argument) {
      std::cout << "failure reading integer" << std::endl;
      validityData->validData = false;
    }
  } else {
    *dataType = DataType::None;
    neighborsSizes = new int[territoriesCount];
  }
    
}

 void MapLoader::PreprocessBorders(std::string line, DataType* dataType) {
  std::vector<std::string> words = Split(line);
  if (words.size() > 0) {
    if (words.size() < 2) {
      validityData->validData = false;
      std::cout << "Error, territory has no edges... invalid map file"
                << std::endl;
    }
    try {
      neighborsSizes[std::stoi(words[0]) - 1] = words.size() - 1;
    } catch (std::invalid_argument) {
      std::cout << "failure reading integer" << std::endl;
      validityData->validData = false;
    }
  } else
    *dataType = DataType::None;
}

 void MapLoader::ProcessBorders(std::string line, DataType* dataType) {
  std::vector<std::string> words = Split(line);
  if (words.size() > 0) {
    if (words.size() < 2) {
      validityData->validData = false;
      std::cout << "Error, territory has no edges... invalid map file"
                << std::endl;
    }
    try {
      std::vector<Territory*>* terrs = generatedMap->GetTerritories();
      Territory* territory =
          (*generatedMap->GetTerritories())[std::stoi(words[0]) - 1];
      for (int i = 0; i < words.size(); i++)
        territory->AddNeighbor(
            (*generatedMap->GetTerritories())[std::stoi(words[i]) - 1]);

    } catch (std::invalid_argument) {
      std::cout << "failure reading integer" << std::endl;
      validityData->validData = false;
    }
  } else
    *dataType = DataType::None;
}

void MapLoader::ProcessContinents(std::string line, DataType* dataType) {
  std::vector<std::string> words = Split(line);

  if (words.size() > 0) {
    if (words.size() != 3) validityData->validData = false;
    Continent* continent =
        new Continent(continentsSizes[index], words[0]);
    continents.push_back(continent);
    index++;
    try {
    } catch (std::invalid_argument) {
      std::cout << "failure reading integer" << std::endl;
      validityData->validData = false;
    }

  } else {
    *dataType = DataType::None;
    generatedMap = new Map(territoriesCount, &continents);
  }
}

void MapLoader::ProcessTerritories(std::string line, DataType* dataType) {
  std::vector<std::string> words = Split(line);
  if (words.size() > 0) {
    if (words.size() < 3) validityData->validData = false;
    std::string* name = new std::string(words[1]);
    Territory* territory = new Territory(name);
    try {
      generatedMap->AddTerritory(territory);
      //continents[std::stoi(words[2]) - 1]->AddTerritory(territory);
      territory->SetContinent(continents[std::stoi(words[2]) - 1]);

    } catch (std::invalid_argument) {
      std::cout << "failure reading integer" << std::endl;
      validityData->validData = false;
    }
  } else
    *dataType = DataType::None;
}
void MapLoader::ReadFile(std::string path) {
  std::string line;
  std::ifstream myfile(path);
  DataType dataType = DataType::None;
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      std::regex title("\\[[a-z]+\\]");
      std::smatch m;
      if (regex_search(line, m, title)) {
        if (m.str().compare("[files]") == 0) {
          validityData->filesFound = true;
        } else if (m.str().compare("[continents]") == 0) {
          dataType = DataType::Continents;
          validityData->continentsFound = true;
        } else if (m.str().compare("[countries]") == 0) {
          dataType = DataType::Territories;
          validityData->territoriesFound = true;
        } else if (m.str().compare("[borders]") == 0) {
          dataType = DataType::Borders;
          validityData->bordersFound = true;
        }
      } else {
        switch (dataType) {
          case (DataType::Continents):
            PreprocessContinents(line, &dataType);
            break;
          case (DataType::Territories):
            PreprocessTerritories(line, &dataType);
            break;
          case (DataType::Borders):
             PreprocessBorders(line, &dataType);
            break;
        }
      }
    }
    myfile.close();
  } else
    std::cout << "Unable to open file";
  myfile = std::ifstream(path);
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      // std::cout << line << std::endl;
      std::regex title("\\[[a-z]+\\]");
      std::smatch m;
      if (regex_search(line, m, title)) {
        if (m.str().compare("[files]") == 0) {
        } else if (m.str().compare("[continents]") == 0) {
          dataType = DataType::Continents;
        } else if (m.str().compare("[countries]") == 0) {
          dataType = DataType::Territories;
        } else if (m.str().compare("[borders]") == 0) {
          dataType = DataType::Borders;
        }
      } else {
        switch (dataType) {
          case (DataType::Continents):
            ProcessContinents(line, &dataType);
            break;
          case (DataType::Territories):
            ProcessTerritories(line, &dataType);
            break;
          case (DataType::Borders):
            ProcessBorders(line, &dataType);
            break;
        }
      }
    }
    myfile.close();
  } else
    std::cout << "Unable to open file";
}

Map* MapLoader::GenerateMap(std::string filePath) {
  ReadFile(filePath);
  if (validityData->IsValid())
    std::cout << "This is a valid map file" << std::endl;
  else
    std::cout << "This is not a valid map" << std::endl;
  for (int i = 0; i < continentsCount; i++)
    std::cout << continentsSizes[i] << std::endl;
  std::cout << territoriesCount << std::endl;
  return generatedMap;
}

MapLoader::MapLoader() {
  validityData = new ValidityData();
  index = 0;
}

MapLoader::~MapLoader() { delete validityData; }
