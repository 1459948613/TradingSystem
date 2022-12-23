#pragma once
#include "BondProductService.hpp"
using namespace std;

class BondInquiryServiceConnector : public Connector<Inquiry<Bond>> {
private:
	BondInquiryService* bondInquiryService;
	BondProductService* bondProductService;
	double TransToPrice(string& s) {
		int n = s.length();
		if (s[n - 1] == '+')
			s[n - 1] = '4';
		return stoi(s.substr(0, n - 4)) + stoi(s.substr(n - 3, 2)) / 32.0 + stoi(s.substr(n - 1, 1)) / 256.0;
	}

public:
	BondInquiryServiceConnector(BondInquiryService* _bondInquiryService, BondProductService* _bondProductService) {
		bondInquiryService = _bondInquiryService;
		bondProductService = _bondProductService;
	}
	virtual void Publish(Inquiry<Bond>& data) override {}
	virtual void Subscribe() override {
		ifstream input;
		input.open("inquiries.txt");
		string row;

		while (getline(input, row)) {
			stringstream line(row);
			string temp;

			getline(line, temp, ',');
			string inquiry_ID = temp;

			getline(line, temp, ',');
			auto bond = bondProductService->GetData(temp);

			getline(line, temp, ',');
			Side side = (temp == "BUY" ? BUY : SELL);

			getline(line, temp, ',');
			long quantity = stol(temp);

			getline(line, temp, ',');
			double quote = TransToPrice(temp);

			getline(line, temp, ',');
			InquiryState state_ = RECEIVED;

			Inquiry<Bond> inquiry(inquiry_ID, bond, side, quantity, quote, state_);
			bondInquiryService->OnMessage(inquiry);
		}
		return;
	}
};