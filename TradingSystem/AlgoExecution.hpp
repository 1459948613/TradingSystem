#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include "BondMarketDataService.hpp"
#include "executionservice.hpp"
using namespace std;

class AlgoExecution {
private:
	static int orderID;
	ExecutionOrder<Bond> executionOrder;
	string FillCast(string v, int w, char c) {
		string res;
		stringstream inter;
		inter << setw(w) << setfill(c) << v;
		inter >> res;
		return res;
	}
public:
	AlgoExecution() {
		
	}
	AlgoExecution(ExecutionOrder<Bond> _executionOrder) : executionOrder(_executionOrder) {}
	void RunAlgo(OrderBook<Bond> orderbook) {
		auto bond = orderbook.GetProduct();
		if (bond.GetProductId() != executionOrder.GetProduct().GetProductId()) {
			return;
		}
		auto orderid = FillCast(to_string(orderID), 8, '0');
		OrderType orderType;
		int rd = rand() % 5;
		switch (rd) {
			case 0:orderType = FOK; 
			break;
			case 1:orderType = IOC; 
			break;
			case 2:orderType = MARKET; 
			break;
			case 3:orderType = LIMIT;
			break;
			case 4:orderType = STOP; 
			break;
		}
		PricingSide pricingside = (rand() % 2 == 0 ? BID : OFFER);
		auto bidorder = orderbook.GetBidStack().begin();
		auto askorder = orderbook.GetOfferStack().begin();
		double price;
		long long visiableQ = 0;
		long long hiddenQ;
		if (pricingside == BID) {
			price = bidorder->GetPrice();
			if (askorder->GetPrice() - bidorder->GetPrice() < 2.5 / 256) {
				visiableQ = bidorder->GetPrice();
			}
			hiddenQ = 2 * visiableQ;
		}
		string parentID = "P" + orderid;
		executionOrder = ExecutionOrder<Bond>(bond, pricingside, orderid, orderType, price, visiableQ, hiddenQ, parentID, true);
		orderID++;
		return;

	}
	ExecutionOrder<Bond> GetExecutionOrder() const {
		return executionOrder;
	}
};