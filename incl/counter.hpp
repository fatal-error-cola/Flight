#ifndef COUNTER_HPP
#define COUNTER_HPP

template<class D>
struct Counter {
	inline static int count = 0;
	static void SetCounter(int c) { count = c; }
	Counter() { ++count; }
};

#endif