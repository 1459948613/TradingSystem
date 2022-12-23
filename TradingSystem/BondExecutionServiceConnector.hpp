#pragma once
#include <string>
#include <iostream>
#include "soa.hpp"
#include "products.hpp"
#include "executionservice.hpp"

class BondExecutionServiceConnector : public Connector<ExecutionOrder<Bond>> {
public:
	BondExecutionServiceConnector() {}
	virtual void Publish(ExecutionOrder<Bond>& data) override {
		auto bond = data.GetProduct();
		string oderType;
		switch (data.GetOrderType()) {
		case FOK: oderType = "FOK"; break;
		case MARKET: oderType = "MARKET"; break;
		case LIMIT: oderType = "LIMIT"; break;
		case STOP: oderType = "STOP"; break;
		case IOC: oderType = "IOC"; break;
		}
		cout << bond.GetProductId() << " OrderId: " << data.GetOrderId() << "\n"
			<< "    PricingSide: " << (data.GetSide() == BID ? "Bid" : "Ask")
			<< " OrderType: " << oderType << " IsChildOrder: " << (data.IsChildOrder() ? "True" : "False")
			<< "\n"
			<< "    Price: " << data.GetPrice() << " VisibleQuantity: " << data.GetVisibleQuantity()
			<< " HiddenQuantity: " << data.GetHiddenQuantity() << "\n" << endl;

		return;
	}
	virtual void Subscribe() override {
		return;
	}
};