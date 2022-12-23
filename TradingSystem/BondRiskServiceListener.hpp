#pragma once
#include "BondRiskService.hpp"
#include "soa.hpp"
using namespace std;

class BondRiskServiceListener : public ServiceListener<Position<Bond>> {
private:
	BondRiskService* bondRiskService;

public:
	BondRiskServiceListener(BondRiskService* _bondRiskService) {
		bondRiskService = _bondRiskService;
	}
	virtual void ProcessAdd(Position<Bond>& data) override {
		bondRiskService->AddPosition(data);
		return;
	}
	virtual void ProcessRemove(Position<Bond>& data) override {};
	virtual void ProcessUpdate(Position<Bond>& data) override {};
};