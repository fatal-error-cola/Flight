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
		enum Type {
			None,
			Breakfast,
			Lunch,
			Supper,
			Snack,
			NUM
		};
		extern QString name[NUM];
	}
}

#endif
