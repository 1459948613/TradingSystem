#pragma once
#include <iostream>
#include <map>
#include "products.hpp"
#include "soa.hpp"
using namespace std;

class BondProductService : public Service<string, Bond> {
private:
	map<string, Bond> mapBond;
public:
	BondProductService() {
		mapBond = map<string, Bond>();
	}
	Bond& GetData(string productId) {
		return mapBond[productId];
	}
	void Add(Bond& bond) {
		mapBond.insert(pair<string, Bond>(bond.GetProductId(), bond));
	}
	vector<Bond> GetBonds(string& ticker) {
		vector<Bond> res;
		for (auto i = mapBond.begin(); i != mapBond.end(); ++i) {
			if ((i->second).GetTicker() == ticker)
				res.push_back(i->second);
		}
		return res;
	}
	virtual void OnMessage(Bond& data) override {}
	virtual void AddListener(ServiceListener<Bond>* listener) override {}
	//virtual const vector<ServiceListener<Bond>*>& GetListeners() const override {}
};