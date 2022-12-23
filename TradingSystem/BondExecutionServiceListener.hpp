#pragma once
#include "BondAlgoExecutionService.hpp"
#include "BondExecutionService.hpp"
#include "soa.hpp"
using namespace std;

class BondExecutionServiceListener : public ServiceListener<AlgoExecution> {
private:
	BondExecutionService* bondExecutionService;
public:
	BondExecutionServiceListener(BondExecutionService* _bondExecutionService) {
		bondExecutionService = _bondExecutionService;
	}
	virtual void ProcessAdd(AlgoExecution& data) override {
		auto order = data.GetExecutionOrder();
		bondExecutionService->AddAlgoExecution(data);
		bondExecutionService->ExecuteOrder(order, BROKERTEC);
		return;
	}
	virtual void ProcessRemove(AlgoExecution& data) override {}
	virtual void ProcessUpdate(AlgoExecution& data) override {}
};