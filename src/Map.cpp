#include "Graph.cpp"
#include "Territory.cpp"

class Map : public Graph<Territory> {
private:
public:
	Map(int size) : Graph(size){
	}
};