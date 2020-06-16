#ifndef COUNTER_HPP
#define COUNTER_HPP

#include <cstddef>
using std::size_t;

template<class D>
struct Counter {
	inline static size_t count = 0;
	static void SetCounter(size_t c) { count = c; }
	Counter() { ++count; }
};

#endif
