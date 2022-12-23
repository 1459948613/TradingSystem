#pragma once
#include "soa.hpp"
#include "products.hpp"
#include <string>
#include <boost/date_time.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include "pricingservice.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
using namespace std;
using namespace boost::posix_time;

class PriceWithTimeStamp : public Price<Bond> {
private:
	ptime timeStamp;
public:
	PriceWithTimeStamp(ptime _timeStamp, Price<Bond> _price)
		:Price<Bond>(_price) {
		timeStamp = _timeStamp;
	}

	ptime GetTimeStamp() {
		return timeStamp;
	}
};

class GUIServiceConnector : public Connector<PriceWithTimeStamp> {
public:
	GUIServiceConnector() {}
	virtual void Subscribe() override {}
	virtual void Publish(PriceWithTimeStamp& data) override {
		auto timeStamp = data.GetTimeStamp();
		auto bond = data.GetProduct();
		auto mid = data.GetMid();
		auto spread = data.GetBidOfferSpread();

		ofstream out;
		out.open("gui.txt", ios::app);
		out << timeStamp << "," << bond.GetProductId() << "," << mid << "," << spread << endl;

		return;
	}
};