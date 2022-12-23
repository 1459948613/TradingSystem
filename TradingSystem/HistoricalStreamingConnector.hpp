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

class HistoricalStreamingConnector : public Connector<PriceStream<Bond>> {
public:
	HistoricalStreamingConnector() {};
	virtual void Subscribe() override {}
	virtual void Publish(PriceStream<Bond>& data) override {
		auto bond = data.GetProduct();
		auto bidOrder = data.GetBidOrder();
		auto askOrder = data.GetOfferOrder();

		ofstream out;
		out.open("streaming.txt", ios::app);
		out << bond.GetProductId() << ","
			<< bidOrder.GetPrice() << "," << bidOrder.GetVisibleQuantity()
			<< "," << bidOrder.GetHiddenQuantity()
			<< "," << askOrder.GetPrice() << "," << askOrder.GetVisibleQuantity()
			<< "," << askOrder.GetHiddenQuantity()
			<< endl;

		return;
	}
};