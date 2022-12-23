#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "BondTradeBookingService.hpp"
#include "BondExecutionService.hpp"
#include "executionservice.hpp"
#include "soa.hpp"
#include "products.hpp"
using namespace std;

class BondTradeBookingServiceListener : public ServiceListener<ExecutionOrder<Bond>> {
private:
	BondTradeBookingService* bondTradeBookingService;

public:
	BondTradeBookingServiceListener(BondTradeBookingService* _bondTradeBookingService) {
		bondTradeBookingService = _bondTradeBookingService;
	}
	virtual void ProcessAdd(ExecutionOrder<Bond>& data) override {
		auto bond = data.GetProduct();
		auto price = data.GetPrice();
		auto visibleQuantity = data.GetVisibleQuantity();
		Side side;
		if (data.GetSide() == BID) {
			side = SELL;
		}
		else {
			side = BUY;
		}
		string book = "Book";
		string tradeID = "Execution";
		Trade<Bond> trade(bond, tradeID, price, book, visibleQuantity, side);
		bondTradeBookingService->BookTrade(trade);
		return;
	}
};