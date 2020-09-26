#pragma once
#include "Map.h"
#include <fstream>
#include <iostream>
#include <regex>


class MapLoader {
 public:
  MapLoader();
  ~MapLoader();
  Map* GenerateMap(std::string filePath);

 private:
  struct ValidityData {
    bool filesFound = false;
    bool continentsFound = false;
    bool territoriesFound = false;
    bool bordersFound = false;
    bool validData = true;

    inline bool IsValid() {
      return filesFound && continentsFound && territoriesFound &&
             bordersFound && validData;
    }
  };

  enum DataType { Continents = 0, Territories, Borders, None };

  Map* generatedMap;
  std::vector<Continent*> continents; 
  int continentsCount;
  int index;
  int territoriesCount;
  int* continentsSizes;
  int* neighborsSizes;
  ValidityData* validityData;
  std::vector<std::string> Split(std::string line) const;
  void PreprocessContinents(std::string line, DataType* dataType);
  void PreprocessTerritories(std::string line, DataType* dataType);
  void PreprocessBorders(std::string line, DataType* dataType);
  void ProcessContinents(std::string line, DataType* dataType);
  void ProcessTerritories(std::string line, DataType* dataType);
  void ProcessBorders(std::string line, DataType* dataType);
  void ReadFile(std::string path);
};
