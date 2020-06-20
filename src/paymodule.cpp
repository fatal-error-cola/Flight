#include "paymodule.hpp"
#include "models.hpp"

PayModule::PayModule(const QString &pay_handle_):
		pay_handle(pay_handle_) { }

PayModule::~PayModule() {
	if(!finished) finishOrder();
}

std::unique_ptr<PayModule> PayModule::reserveOrder(const OrderInfo &order_info, int cost) {
	auto pay_handle = order_info.customer.pay_handle;
	return std::unique_ptr<PayModule>(new PayModule(pay_handle));
}

void PayModule::finishOrder() { finished = true; }
