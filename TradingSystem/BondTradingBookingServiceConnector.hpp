#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include "soa.hpp"
#include "BondTradeBookingService.hpp"
#include "tradebookingservice.hpp"
#include "BondProductService.hpp"
using namespace std;

class BondTradingBookingServiceConnector : public Connector<Trade<Bond>> {
private:
	BondTradeBookingService* bondTradeBookingService;
	BondProductService* bondProductService;
	double TransToPrice(string s) {
		int n = s.length();
		if (s[n - 1] == '+') {
			s[n - 1] = '4';
		}
		return stoi(s.substr(0, n - 4)) + stoi(s.substr(n - 3, 2)) / 32.0 + stoi(s.substr(n - 1, 1)) / 256.0;
	}

public:
	BondTradingBookingServiceConnector(BondTradeBookingService* _bondTradeBookingService, BondProductService* _bondProductService) {
		bondTradeBookingService = _bondTradeBookingService;
		bondProductService = _bondProductService;
	}
	virtual void Publish(Trade<Bond>& data) override {}
	virtual void Subscribe() override {
		ifstream input;
		input.open("trades.txt");

		string row;
		while (getline(input, row)) {
			stringstream line(row);
			string temp;
			getline(line, temp, ',');
			auto bond = bondProductService->GetData(temp);

			getline(line, temp, ',');
			auto tradeID = temp;
			getline(line, temp, ',');
			auto price = TransToPrice(temp);
			getline(line, temp, ',');
			auto book = temp;
			getline(line, temp, ',');
			long quantity = stol(temp);
			getline(line, temp, ',');
			Side side = (temp == "BUY" ? BUY : SELL);

			Trade<Bond> bondNew(bond, tradeID, price, book, quantity, side);
			bondTradeBookingService->OnMessage(bondNew);
		}
		return;
	}
};