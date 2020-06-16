#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "models.hpp"
#include "counter.hpp"
#include "singleton.hpp"

class Flights: public Counter<Flights> {
public:
	template<typename ...Args>
	void emplace(Args &&...args) = 0;
};

#endif
