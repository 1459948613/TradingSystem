#pragma once
#include <string>
#include <iostream>
#include "soa.hpp"
#include "streamingservice.hpp"
#include "products.hpp"
using namespace std;

class BondStreamingServiceConnector : public Connector<PriceStream<Bond>> {
public:
	BondStreamingServiceConnector() {

	}
	virtual void Subscribe() override {

	}
	virtual void Publish(PriceStream<Bond>& data) override {
		auto bond = data.GetProduct();
		auto bidOrder = data.GetBidOrder();
		auto askOrder = data.GetOfferOrder();

		cout << bond.GetProductId() << "\n"
			<< "    BidOrder: " << "Price: " << bidOrder.GetPrice() << "  VisibleQuantity: " << bidOrder.GetVisibleQuantity()
			<< "  HiddenQuantity: " << bidOrder.GetHiddenQuantity() << "\n"
			<< "    offerOrder: " << "Price: " << askOrder.GetPrice() << "  VisibleQuantity: " << askOrder.GetVisibleQuantity()
			<< "  HiddenQuantity: " << askOrder.GetHiddenQuantity() << "\n"
			<< endl;

		return;
	}
};