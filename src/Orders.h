#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Order {
public:
	Order();
	Order(const Order& toCopy);
	~Order();

	bool validate();
	void execute();

	friend ostream& operator <<(ostream& outs, const Order& toOutput);
};

class Deploy : public Order {

};

class Advance : public Order {

};

class Bomb : public Order {

};

class Blockade : public Order {

};

class Negotiate : public Order {

};

class Airlift : public Order {

};

class OrdersList {
public:
	OrdersList();
	OrdersList(const OrdersList& toCopy);
	~OrdersList();

	void queue(Order o);
	void move(Order o);
	void remove(Order o); // Used remove instead of delete b/c delete is a reserved keyword which caused an error
	
	friend ostream& operator <<(ostream& outs, const OrdersList& toOutput);
private:
	std::vector<Order> *ordersList;
};
