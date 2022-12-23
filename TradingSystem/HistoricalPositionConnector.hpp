#pragma once
#include "soa.hpp"
#include "products.hpp"
#include "historicaldataservice.hpp"
#include "GUIServiceConnector.hpp"
#include "BondStreamingService.hpp"
#include "BondRiskService.hpp"
#include "BondPositionService.hpp"
#include "BondExecutionService.hpp"
#include "BondInquiryService.hpp"
#include <string>
#include <iostream>
using namespace std;

class HistoricalPositionConnector : public Connector<Position<Bond>> {
public:
	HistoricalPositionConnector() {};
	virtual void Subscribe() override {}
	virtual void Publish(Position<Bond>& data) override {
		auto bond = data.GetProduct();
		auto position = data.GetAggregatePosition();

		ofstream out;
		out.open("positions.txt", ios::app);
		out << bond.GetProductId() << "," << position << endl;

		return;
	}
};