#pragma once
#include <string>
#include "soa.hpp"
#include "products.hpp"
#include "BondHistoricalDataService.hpp"
using namespace std;

class HistoricalStreamingListener : public ServiceListener<PriceStream<Bond>> {
private:
	BondHistoricalStreamingService* service;

public:
	HistoricalStreamingListener(BondHistoricalStreamingService* p) :service(p) {}

	virtual void ProcessAdd(PriceStream<Bond>& data) override {
		service->PersistData(data.GetProduct().GetProductId(), data);
		return;
	}
	virtual void ProcessRemove(PriceStream<Bond>& data) override {}
	virtual void ProcessUpdate(PriceStream<Bond>& data) override {}
};