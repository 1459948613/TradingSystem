#pragma once
#include "pricingservice.hpp"
#include "products.hpp"
#include "soa.hpp"
#include <map>
#include <vector>
using namespace std;

class BondPricingService : public PricingService<Bond> {
private:
	map<string, Price<Bond> > mapPrice;
	vector<ServiceListener<Price<Bond>>* > listenerList;
public:
	BondPricingService() {
		mapPrice = map<string, Price<Bond>>();
	}
	virtual Price<Bond>& GetData(string s) override {
		return mapPrice.at(s);
	}
	virtual void OnMessage(Price<Bond>& p) override {
		auto id = p.GetProduct().GetProductId();
		if (mapPrice.find(id) != mapPrice.end()) {
			mapPrice.erase(id);
		}
		mapPrice.insert(pair<string, Price<Bond>>(id, p));
		for (auto& listener : listenerList) {
			listener->ProcessAdd(p);
		}
		return;
	}
	virtual void AddListener(ServiceListener<Price<Bond>>* listener) override {
		listenerList.push_back(listener);
		return;
	}
	virtual const vector< ServiceListener<Price<Bond>>*>& GetListeners() const {
		return listenerList;
	}
};