#pragma once
#include <string>
#include "soa.hpp"
#include "products.hpp"
#include "BondHistoricalDataService.hpp"
using namespace std;

class HistoricalAllInquriesListener : public ServiceListener<Inquiry<Bond> > {
private:
	BondHistoricalAllInquiriesService* service;

public:
	HistoricalAllInquriesListener(BondHistoricalAllInquiriesService* p) :service(p) {}
	virtual void ProcessAdd(Inquiry<Bond>& data) override {
		service->PersistData(data.GetInquiryId(), data);
		return;
	}
	virtual void ProcessRemove(Inquiry<Bond>& data) override {}
	virtual void ProcessUpdate(Inquiry<Bond>& data) override {}

};