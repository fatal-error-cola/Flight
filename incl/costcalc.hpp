#ifndef COSTCALC_HPP
#define COSTCALC_HPP

struct Flight;

struct CostCalc {
	int operator()(Flight *flight, int class_type, int tickets) const;
	int operator()(Flight *flight, int class_type, int tickets, bool transfer) const;
	int operator()(Flight *flight, int class_type, int adults, int children) const;
	int operator()(Flight *flight, int class_type, int adults, int children, bool transfer) const;
};

#endif
