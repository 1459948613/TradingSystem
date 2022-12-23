#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "soa.hpp"
#include "products.hpp"
#include "marketdataservice.hpp"
#include "BondProductService.hpp"
#include "BondMarketDataService.hpp"
using namespace std;

class BondMarketDataServiceConnector : public Connector<OrderBook<Bond>> {
private:
	BondMarketDataService* bondMarketDataService;
	BondProductService* bondProductService;
	double TransToPrice(string& s) {
		int n = s.length();
		if (s[n - 1] == '+') { 
			s[n - 1] = '4'; 
		}
		return stoi(s.substr(0, n - 4)) + stoi(s.substr(n - 3, 2)) / 32.0 + stoi(s.substr(n - 1, 1)) / 256.0;
	}
public:
	BondMarketDataServiceConnector(BondMarketDataService* _bondMarketDataService, BondProductService* _bondProductService) {
		bondMarketDataService = _bondMarketDataService;
		bondProductService = _bondProductService;
	}
	virtual void Publish(OrderBook<Bond>& data) override {
		return;
	}
	virtual void Subscribe() override {
		ifstream input;
		input.open("marketdata.txt");
		string row;

		while (getline(input, row)) {
			stringstream line(row);
			string temp;
			vector<Order> bid, ask;

			getline(line, temp, ',');
			auto bond = bondProductService->GetData(temp);

			for (int i = 0; i < 10; ++i) {
				getline(line, temp, ',');
				auto price = TransToPrice(temp);
				getline(line, temp, ',');
				auto quantity = stol(temp);
				getline(line, temp, ',');
				auto side = temp;
				if (i < 5) {
					bid.push_back(Order(price, quantity, BID));
				}
				else {
					ask.push_back(Order(price, quantity, OFFER));
				}
			}

			OrderBook<Bond> orderbook(bond, bid, ask);
			bondMarketDataService->OnMessage(orderbook);
		}
		return;
	}
};