#pragma once
#include <string>
#include "soa.hpp"
#include "products.hpp"
#include "BondHistoricalDataService.hpp"
using namespace std;

class HistoricalExecutionListener : public ServiceListener<ExecutionOrder<Bond>> {
private:
	BondHistoricalExecutionService* service;

public:
	HistoricalExecutionListener(BondHistoricalExecutionService* p) :service(p) {}

	virtual void ProcessAdd(ExecutionOrder<Bond>& data) override {
		service->PersistData(data.GetOrderId(), data);
		return;
	}
	virtual void ProcessRemove(ExecutionOrder<Bond>& data) override {}
	virtual void ProcessUpdate(ExecutionOrder<Bond>& data) override {}
};