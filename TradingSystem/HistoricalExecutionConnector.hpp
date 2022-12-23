#pragma once
#include "soa.hpp"
#include "historicaldataservice.hpp"
#include "GUIServiceConnector.hpp"
#include "BondStreamingService.hpp"
#include "BondRiskService.hpp"
#include "BondPositionService.hpp"
#include "BondExecutionService.hpp"
#include "BondInquiryService.hpp"
#include "GUIServiceConnector.hpp"
#include "products.hpp"
#include <string>
#include <iostream>
using namespace std;

class HistoricalExecutionConnector : public Connector<ExecutionOrder<Bond>> {
public:
	HistoricalExecutionConnector() {};
	virtual void Subscribe() override {}
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
		ofstream out;
		out.open("executions.txt", ios::app);
		out << bond.GetProductId() << "," << data.GetOrderId()
			<< "," << (data.GetSide() == BID ? "Bid" : "Ask")
			<< "," << oderType << "," << (data.IsChildOrder() ? "True" : "False")
			<< "," << data.GetPrice()
			<< "," << data.GetVisibleQuantity()
			<< "," << data.GetHiddenQuantity() << endl;
		return;
	}
};
