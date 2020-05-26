#include <cstdio>
#include "counter.hpp"

class A: Counter<A> {
public:
	A() { printf("%d\n", count); }
};

int main() {
	A a;
	A b;
	A c;
	return 0;
}
