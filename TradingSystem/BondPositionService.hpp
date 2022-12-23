#pragma once
#include "BondTradeBookingService.hpp"
#include "positionservice.hpp"
using namespace std;

class BondPositionService : public PositionService<Bond> {
private:
	map<string, Position<Bond> >positionMap;
	vector<ServiceListener<Position<Bond> >*> listenerList;
public:
	BondPositionService() {
		positionMap = map<string, Position<Bond>>();
	}
	virtual Position<Bond>& GetData(string id) override {
		return positionMap[id];
	}
	virtual void OnMessage(Position<Bond>& position) override {
		return;
	}
	virtual void AddListener(ServiceListener<Position<Bond> >* listener) override {
		listenerList.push_back(listener);
		return;
	}
	virtual const vector<ServiceListener<Position<Bond> >*>& GetListeners() const {
		return listenerList;
	}
	virtual void AddTrade(const Trade<Bond>& trade) override {
		long quantity = trade.GetQuantity();
		if (trade.GetSide() == SELL)
			 quantity = -quantity;
		auto bond = trade.GetProduct();
		auto id = bond.GetProductId();

		auto it = positionMap.find(id);
		if (it != positionMap.end()) {
			(it->second).AddPosition(trade.GetBook(), quantity);
		}
		else {
			positionMap.insert(pair<string, Position<Bond> >(id, Position<Bond>(bond)));
			AddTrade(trade);
			return;
		}

		for (auto& listener : listenerList) {
			listener->ProcessAdd(it->second);
		}
		return;
	}
};