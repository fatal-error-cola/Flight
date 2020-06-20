#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <QString>

namespace Class {
	enum Type {
		Economy,
		PremiumEconomy,
		Business,
		First,
		NUM
	};
	extern QString name[NUM];
}

namespace Server {
	namespace Meal {
		constexpr unsigned NUM = 4;
		enum Type {
			None = 0x0,
			Breakfast = 0x1,
			Lunch = 0x2,
			Supper = 0x4,
			Snack = 0x8
		};
		extern QString name[NUM];
	}
}

#endif
