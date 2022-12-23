#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "tradebookingservice.hpp"
#include "soa.hpp"
#include "products.hpp"
using namespace std;

class BondTradeBookingService : public TradeBookingService<Bond> {
private:
	map<string, Trade<Bond>> mapTrade;
	vector<ServiceListener<Trade<Bond>>*> listenerList;
public:
	BondTradeBookingService() {
		mapTrade = map<string, Trade<Bond>>();
	}
	virtual Trade<Bond>& GetData(string id) override {
		return mapTrade.at(id);
	}
	virtual void OnMessage(Trade<Bond>& trade) override {
		BookTrade(trade);
		return;
	}
	virtual void AddListener(ServiceListener<Trade<Bond>>* listener) override {
		listenerList.push_back(listener);
		return;
	}
	virtual const vector<ServiceListener<Trade<Bond>>*>& GetListeners() const {
		return listenerList;
	}
	virtual void BookTrade(Trade<Bond> trade) {
		auto id = trade.GetProduct().GetProductId();
		if (mapTrade.find(id) != mapTrade.end()) {
			mapTrade.erase(id);
		}
		mapTrade.insert(pair<string, Trade<Bond>>(id, trade));
		for (auto& listener : listenerList) {
			listener->ProcessAdd(trade);
		}
		return;
	}
};