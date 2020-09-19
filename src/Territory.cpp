#include <vector>
#include <string>
#include "Continent.h"
#include "Player.h"

class Territory {
private:
	std::string* name;
	Continent* continent;
	Player* player;
	int troops;
	std::vector<Territory*> neighbors;
public:
	Territory(std::string* name) {
		this->name = name;
		troops = 0;
	}

	std::string* GetName() {
		return this->name;
	}

	void SetContinent(Continent* continent) {
		this->continent = continent;
	}

	Continent* GetContinent() {
		return this->continent;
	}

	void SetPlayer(Player* player) {
		this->player = player;
	}

	Player* GetPlayer() {
		return this->player;
	}

	void IncreaseTroops(int increase) {
		this->troops += increase;
	}

	void DecraseTroops(int decrease) {
		this->troops -= decrease;
	}

	int GetTroops() {
		return this->troops;
	}

	// TODO: check if this can be done more efficiently.
	void AddNeighbor(Territory* neighbor) {
		this->neighbors.push_back(neighbor);
	}

	std::vector<Territory*>* GetNeighbors() {
		return &this->neighbors;
	}
};