#pragma once
#include <string>
#include "soa.hpp"
#include "products.hpp"
#include "BondHistoricalDataService.hpp"
using namespace std;

class HistoricalRiskListener : public ServiceListener<PV01<Bond>> {
private:
	BondHistoricalRiskService* service;

public:
	HistoricalRiskListener(BondHistoricalRiskService* p) :service(p) {}

	virtual void ProcessAdd(PV01<Bond>& data) override {
		service->PersistData(data.GetProduct().GetProductId(), data);
		return;
	}
	virtual void ProcessRemove(PV01<Bond>& data) override {}
	virtual void ProcessUpdate(PV01<Bond>& data) override {}

};
