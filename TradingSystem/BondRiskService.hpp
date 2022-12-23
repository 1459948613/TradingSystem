#pragma once
#include "BondPositionService.hpp"
#include "riskservice.hpp"
#include "BondInformation.h"
using namespace std;

class BondRiskService : public RiskService<Bond> {
private:
	map<string, PV01<Bond> > pv01Map;
	vector<ServiceListener<PV01<Bond> >*> listenerList;

public:
	BondRiskService() {
		pv01Map = map<string, PV01<Bond>>();
	}
	virtual PV01<Bond>& GetData(string id) override {
		return pv01Map[id];
	}
	virtual void OnMessage(PV01<Bond>& pv01) override {
		return; 
	}
	virtual void AddListener(ServiceListener<PV01<Bond> >* listener) override {
		listenerList.push_back(listener);
		return;
	}
	virtual const vector<ServiceListener<PV01<Bond> >*>& GetListeners() const {
		return listenerList;
	}
	virtual void AddPosition(Position<Bond>& position) {
		auto bond = position.GetProduct();
		auto id = bond.GetProductId();
		auto it = pv01Map.find(id);

		long quantity = position.GetAggregatePosition();

		if (it != pv01Map.end()) {
			(it->second).AddQuantity(quantity);
		}
		else {
			pv01Map.insert(pair<string, PV01<Bond> >(id, PV01<Bond>(bond, bondRisk[id], quantity)));
		}
		it = pv01Map.find(id);

		for (auto& listener : listenerList) {
			listener->ProcessAdd(it->second);
		}

		return;
	}
	virtual double GetBucketedRisk(const BucketedSector<Bond>& sector) const override {
		double res = 0;
		for (auto& product : sector.GetProducts()) {
			res += pv01Map.at(product.GetProductId()).GetPV01();
		}
		return res;
	}
};