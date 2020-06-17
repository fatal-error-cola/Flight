#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <QStringList>

namespace Class {
	enum Type {
		Economy,
		PremiumEconomy,
		Business,
		First,
		NUM
	};
	extern QStringList name;
}

namespace Server {
	namespace Meal {
		constexpr int NUM = 4;
		enum Type {
			None = 0x0,
			Breakfast = 0x1,
			Lunch = 0x2,
			Supper = 0x4,
			Snack = 0x8
		};
		extern QStringList name;
	}
}

#endif
