#pragma once
#include "BondPositionService.hpp"
#include "soa.hpp"
using namespace std;

class BondPositionServiceListener : public ServiceListener<Trade<Bond>> {
private:
	BondPositionService* bondPositionService;

public:
	BondPositionServiceListener(BondPositionService* _bondPositionService) {
		bondPositionService = _bondPositionService;
	}
	virtual void ProcessAdd(Trade<Bond>& data) {
		bondPositionService->AddTrade(data);
		return;
	}
	virtual void ProcessRemove(Trade<Bond>& data) override {}
	virtual void ProcessUpdate(Trade<Bond>& data) override {}
};