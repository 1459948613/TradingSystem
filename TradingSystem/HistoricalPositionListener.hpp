#pragma once
#include <string>
#include "soa.hpp"
#include "products.hpp"
#include "BondHistoricalDataService.hpp"
using namespace std;

class HistoricalPositionListener : public ServiceListener<Position<Bond>> {
private:
	BondHistoricalPositionService* service;

public:
	HistoricalPositionListener(BondHistoricalPositionService* p) :service(p) {}

	virtual void ProcessAdd(Position<Bond>& data) override {
		service->PersistData(data.GetProduct().GetProductId(), data);
		return;
	}
	virtual void ProcessRemove(Position<Bond>& data) override {}
	virtual void ProcessUpdate(Position<Bond>& data) override {}
};