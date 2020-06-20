#include "models.hpp"
#include <utility>
#include <QJsonArray>
#include "helpers.hpp"
#include "containers.hpp"

Airport::Airport(unsigned index_, const QJsonObject &json):
		index(index_),
		ICAO(json["ICAO"].toString()),
		IATA(json["IATA"].toString()),
		name(json["name"].toString()),
		city(json["city"].toString()),
		time_zone(json["timezone"].toString().toUtf8()) { }

QJsonObject FlightInfo::toJson() const {
	QJsonArray server_jsonarray;
	for(unsigned i = 0; i < Server::Meal::NUM; ++i)
		if(server.meal & 1 << i) server_jsonarray.append(Server::Meal::name[i]);
	if(server.hasWiFi) server_jsonarray.append("Wi-Fi");
	QJsonValue server_json;
	if(!server_jsonarray.empty()) server_json = std::move(server_jsonarray);
	return {
		{"flight", flight},
		{"airline", airline},
		{"aircraft", aircraft},
		{"depart", QJsonObject({
			{"airport", depart.airport->name},
			{"terminal", depart.terminal},
			{"time", depart.time.toString("yyyy.MM.dd hh:mm")}})},
		{"arrive", QJsonObject({
			{"airport", arrive.airport->name},
			{"terminal", arrive.terminal},
			{"time", arrive.time.toString("yyyy.MM.dd hh:mm")}})},
		{"duration", depart.time.secsTo(arrive.time) / 60},
		{"server", std::move(server_json)},
	};
}

OrderInfo::OrderInfo(const QJsonObject &json) {
	customer.pay_handle = json["pay_handle"].toString();
	customer.tel = json["tel"].toString();
	auto &&tickets = json["tickets"].toObject();
	for(const QJsonValue &item : tickets["adults"].toArray())
		adults.push_back({item["name"].toString(), item["document"].toString()});
	for(const QJsonValue &item : tickets["children"].toArray())
		children.push_back({item["name"].toString(), item["document"].toString()});
	for(const QJsonValue &item : json["flights"].toArray())
		flights.push_back({item["index"].toInt(), item["class"].toInt()});
}

// QJsonObject OrderInfo::toJson() const {
// 	QJsonArray json_adults;
// 	for(auto &&adult : adults) {
// 		QJsonObject item;
// 		item["name"] = adult.name;
// 		item["document"] = adult.document;
// 		json_adults.append(std::move(item));
// 	}
// 	QJsonArray json_children;
// 	for(auto &&child : children) {
// 		QJsonObject item;
// 		item["name"] = child.name;
// 		item["document"] = child.document;
// 		json_children.append(std::move(item));
// 	}
// 	QJsonArray json_flight;
// 	for(auto &&[index, class_type] : flights) {
// 		QJsonObject item;
// 		item["index"] = static_cast<int>(index);
// 		item["class"] = static_cast<int>(class_type);
// 		json_flight.append(std::move(item));
// 	}
// 	return {
// 		{"pay_handle", customer.pay_handle},
// 		{"tel", customer.tel},
// 		{"tickets", JsonObject({
// 			{"adults", std::move(json_adults)},
// 			{"children", std::move(json_children)}})},
// 		{"flights", std::move(json_flight)}
// 	};
// }

QJsonObject Order::toJson() const {
	QJsonArray flights_json;
	for(auto &&[flight_no, class_type] : info.flights) {
		auto *flight = Flights::getInstance()->get(flight_no);
		auto info = flight->info.toJson();
		info["class"] = static_cast<int>(class_type);
		flights_json.append(std::move(info));
	}
	return {
		{"cost", cost},
		{"tickets", QJsonObject({
			{"adults", static_cast<int>(info.adults.size())},
			{"children", static_cast<int>(info.children.size())}})},
		{"flights", std::move(flights_json)},
		{"can_cancel", can_cancel}
	};
}
