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

class HistoricalAllInquiriesConnector : public Connector<Inquiry<Bond>> {
public:
	HistoricalAllInquiriesConnector() {};
	virtual void Subscribe() override {}
	virtual void Publish(Inquiry<Bond>& data) override {
		auto inquiry_id = data.GetInquiryId();
		auto id = data.GetProduct().GetProductId();
		auto price = data.GetPrice();
		auto quantity = data.GetQuantity();

		string side = (data.GetSide() == BUY ? "BUY" : "SELL");
		auto state = data.GetState();
		string state_;
		switch (state) {
		case RECEIVED:state_ = "RECEIVED"; break;
		case QUOTED:state_ = "QUOTED"; break;
		case DONE:state_ = "DONE"; break;
		case REJECTED:state_ = "REJECTED"; break;
		case CUSTOMER_REJECTED:state_ = "CUSTOMER_REJECTED"; break;
		}

		ofstream out;
		out.open("allinquiries.txt", ios::app);
		out << inquiry_id << "," << id << "," << price << "," << quantity << "," << side << "," << state_
			<< endl;

		return;
	}
};