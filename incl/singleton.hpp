#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template<class D>
class Singleton {
	inline static D *instance = nullptr;

	Singleton(const Singleton &) = delete;
	Singleton & operator=(const Singleton &) = delete;

protected:
	Singleton() = default;
	~Singleton() = default;

public:
	template<typename ...Args>
	static D * init(Args ...args) {
		return instance = new D(args...);
	}

	static D * getInstance() {
		return instance;
	}
};

#endif
