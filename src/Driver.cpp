#include "Territory.cpp"
#include <string>
#include <iostream>

int main() {
	Territory t[] = {
		Territory(&std::string("A")),
		Territory(&std::string("B")),
		Territory(&std::string("C")),
		Territory(&std::string("D")),
		Territory(&std::string("E")),
		Territory(&std::string("F")),
		Territory(&std::string("G")),
		Territory(&std::string("H")),
		Territory(&std::string("I")),
		Territory(&std::string("J")),
		Territory(&std::string("K")),
		Territory(&std::string("L")),
	};
	Continent c[4];
	Player p[4];

	t[0].SetContinent(&c[0]);
	t[1].SetContinent(&c[0]);
	t[2].SetContinent(&c[0]);
	t[3].SetContinent(&c[0]);
	t[4].SetContinent(&c[0]);
	t[5].SetContinent(&c[0]);
	t[6].SetContinent(&c[0]);
	t[7].SetContinent(&c[0]);
	t[8].SetContinent(&c[1]);
	t[9].SetContinent(&c[1]);
	t[10].SetContinent(&c[1]);
	t[11].SetContinent(&c[2]);

	t[0].SetPlayer(&p[1]);
	t[1].SetPlayer(&p[1]);
	t[2].SetPlayer(&p[1]);
	t[3].SetPlayer(&p[1]);
	t[4].SetPlayer(&p[1]);
	t[5].SetPlayer(&p[1]);
	t[6].SetPlayer(&p[1]);
	t[7].SetPlayer(&p[0]);
	t[8].SetPlayer(&p[2]);
	t[9].SetPlayer(&p[1]);
	t[10].SetPlayer(&p[0]);
	t[11].SetPlayer(&p[0]);

	t[0].AddNeighbor(&t[1]);
	t[0].AddNeighbor(&t[2]);
	t[0].AddNeighbor(&t[3]);
	t[0].AddNeighbor(&t[4]);

	t[1].AddNeighbor(&t[0]);
	t[1].AddNeighbor(&t[2]);
	t[1].AddNeighbor(&t[6]);
	t[1].AddNeighbor(&t[11]);
}