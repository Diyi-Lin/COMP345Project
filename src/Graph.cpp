#include <vector>

template<typename type>
class Graph {
private:
	std::vector<type*> vertices;
public:
	Graph(int size) {
		this->vertices.reserve(size);
	}

	void AddVertex(type* vertex) {
		this->vertices.push_back(vertex);
	}

	std::vector<type*>* GetVertices() {
		return &this->vertices;
	}
}; 