#include "orderplacement.hpp"
#include "paymodule.hpp"
#include "costcalc.hpp"
#include "logger.hpp"
#include "models.hpp"
#include "containers.hpp"

OrderPlacement::OrderPlacement(QObject *parent):
		QObject(parent) { }

void OrderPlacement::operator()(OrderInfo &&order_info) {
	CostCalc costcalc;
	int cost = 0;
	unsigned ticket_num = order_info.adults.size() + order_info.children.size();

	for(auto &&[flight_no, class_type] : order_info.flights) {
		auto *flight = Flights::getInstance()->get(flight_no);
		if(flight == nullptr || flight->info.classes[class_type].tickets < ticket_num)
			{ emit finished("-1"); return; }
		cost += costcalc(flight, class_type,
			order_info.adults.size(), order_info.children.size(),
			order_info.flights.size() > 1);
	}

	std::unique_ptr<PayModule> pay_module;
	try {
		pay_module = PayModule::reserveOrder(order_info, cost);
	} catch(PayFailed &) {
		emit finished("-2"); return;
	}

	for(auto &&[flight_no, class_type] : order_info.flights) {
		auto *flight = Flights::getInstance()->get(flight_no);
		flight->info.classes[class_type].tickets -= ticket_num;
	}

	order_logger->write(
		QString("Order placed: pay_handle %1, cost %2")
			.arg(order_info.customer.pay_handle)
			.arg(cost));

	unsigned index = Orders::getInstance()->getNewIndex();
	Orders::getInstance()->add({index, cost, std::move(order_info)});

	pay_module->finishOrder();
	emit finished(QByteArray::number(index));
}
