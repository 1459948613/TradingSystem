#include <iostream>
#include <fstream>
#include <cstdlib>
#pragma once
#include <string>
#include "soa.hpp"
#include "pricingservice.hpp"
#include "BondProductService.hpp"
#include "products.hpp"

using namespace std;

class BondPricingServiceConnector : public Connector<Price<Bond>> {
private:
	BondPricingService* bondPricingService;
	BondProductService* bondProductService;
	double TransToPrice(string s) {
		int n = s.length();
		if (s[n - 1] == '+') {
			s[n - 1] = '4';
		}
		return stoi(s.substr(0, n - 4)) + stoi(s.substr(n - 3, 2)) / 32.0 + stoi(s.substr(n - 1, 1)) / 256.0;
	}
public:
	BondPricingServiceConnector(BondPricingService* _bondPricingService, BondProductService* _bondProductService) {
		bondPricingService = _bondPricingService;
		bondProductService = _bondProductService;
	}
	virtual void Subscribe() override {
		ifstream input;
		input.open("prices.txt");

		string row;
		while (getline(input, row)) {
			stringstream line(row);
			string temp;
			getline(line, temp, ',');
			auto bond = bondProductService->GetData(temp);
			getline(line, temp, ',');
			auto price = TransToPrice(temp);
			getline(line, temp, ',');
			auto spread = TransToPrice(temp);
			Price<Bond> bondPrice(bond, price, spread);
			bondPricingService->OnMessage(bondPrice);
		}
		return;
	}
};