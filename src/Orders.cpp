#include "Orders.h"

OrdersList::OrdersList() {
	ordersList = new std::vector<Order>();
}

OrdersList::~OrdersList() {
	delete ordersList;
	ordersList = NULL;
}
