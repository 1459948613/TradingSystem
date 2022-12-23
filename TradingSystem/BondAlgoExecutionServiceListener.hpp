#pragma once
#include "BondAlgoExecutionService.hpp"
#include "soa.hpp"
using namespace std;

class BondAlgoExecutionServiceListener : public ServiceListener<OrderBook<Bond>> {
private:
    BondAlgoExecutionService* bondAlgoExecutionService;
public:
    BondAlgoExecutionServiceListener(BondAlgoExecutionService* _bondAlgoExecutionService) {
        bondAlgoExecutionService = _bondAlgoExecutionService;
    }
    virtual void ProcessAdd(OrderBook<Bond>& data) override {
        bondAlgoExecutionService->AddOrderBook(data);
        return;
    }
    virtual void ProcessRemove(OrderBook<Bond>& data) override {}
    virtual void ProcessUpdate(OrderBook<Bond>& data) override {}
};