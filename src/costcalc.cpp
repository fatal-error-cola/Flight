#include "costcalc.hpp"
#include "models.hpp"

constexpr int children_discount = 70;

int CostCalc::operator()(Flight *flight, int class_type, int tickets) const {
	return (*this)(flight, class_type, tickets, 0, false);
}

int CostCalc::operator()(Flight *flight, int class_type, int tickets, bool transfer) const {
	return (*this)(flight, class_type, tickets, 0, transfer);
}

int CostCalc::operator()(Flight *flight, int class_type, int adults, int children) const {
	return (*this)(flight, class_type, adults, children, false);
}

int CostCalc::operator()(Flight *flight, int class_type, int adults, int children, bool transfer) const {
	int cost = flight->info.classes[class_type].cost;
	cost = cost * adults + cost * children * children_discount / 100;
	if(transfer) cost = cost * flight->transfer_discount / 100;
	return cost;
}
