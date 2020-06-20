#ifndef PAYMODULE_HPP
#define PAYMODULE_HPP

#include <exception>
#include <utility>
#include <memory>
#include <QString>

struct OrderInfo;

struct PayFailed: public std::exception { };

class PayModule {
	QString pay_handle;
	bool finished = false;

	PayModule(const QString &pay_handle);

public:
	~PayModule();
	static std::unique_ptr<PayModule> reserveOrder(const OrderInfo &order_info, int cost);
	void finishOrder();
};

#endif
