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

class HistoricalRiskConnector : public Connector<PV01<Bond>> {
public:
	HistoricalRiskConnector() {};
	virtual void Subscribe() override {}
	virtual void Publish(PV01<Bond>& data) override {
		auto bond = data.GetProduct();
		auto risk = data.GetPV01();

		ofstream out;
		out.open("risk.txt", ios::app);
		out << bond.GetProductId() << "," << risk << endl;

		return;
	}
};