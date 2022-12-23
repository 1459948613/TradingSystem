#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "marketdataservice.hpp"
#include "soa.hpp"
#include "products.hpp"
using namespace std;


class BondMarketDataService :public MarketDataService<Bond> {
private:
	map<string, OrderBook<Bond>> mapOrder;
	vector<ServiceListener<OrderBook<Bond>>*> listenerList;

public:
	BondMarketDataService() {
		mapOrder = map<string, OrderBook<Bond>>();
	}
	virtual OrderBook<Bond>& GetData(string id) override {
		return mapOrder.at(id);
	}
	virtual void OnMessage(OrderBook<Bond>& orderbook) override {
		auto id = orderbook.GetProduct().GetProductId();
		if (mapOrder.find(id) != mapOrder.end()) {
			mapOrder.erase(id);
		}
		mapOrder.insert(pair<string, OrderBook<Bond>>(id, orderbook));
		auto bestorder = GetBestBidOffer(id);
		vector<Order> bid, ask;
		bid.push_back(bestorder.GetBidOrder());
		ask.push_back(bestorder.GetOfferOrder());
		OrderBook<Bond> bestbook = OrderBook<Bond>(orderbook.GetProduct(), bid, ask);

		for (auto& listener : listenerList) {
			listener->ProcessAdd(bestbook);
		}
		return;
	}
	virtual void AddListener(ServiceListener<OrderBook<Bond>>* listener) override {
		listenerList.push_back(listener);
		return;
	}
	virtual const vector<ServiceListener<OrderBook<Bond>>*>& GetListeners() const {
		return listenerList;
	}
	
	virtual BidOffer GetBestOrder(const string& productId) {
		auto orderbook = mapOrder.at(productId);
		auto bid = orderbook.GetBidStack();
		auto ask = orderbook.GetOfferStack();
		auto bestbid = bid[0];
		auto bestask = ask[0];
		for (int i = 0; i < bid.size(); i++) {
			if (bid[i].GetPrice() > bestbid.GetPrice())
				bestbid = bid[i];
		}
		for (int i = 0; i < ask.size(); i++) {
			if (ask[i].GetPrice() < bestask.GetPrice())
				bestask = ask[i];
		}
		BidOffer res = BidOffer(bestbid, bestask);
		return res;
	}
	
	virtual OrderBook<Bond> TotalDepth(const string& productId) {
		auto orderbook = mapOrder.at(productId);
		auto bid = orderbook.GetBidStack();
		auto ask = orderbook.GetOfferStack();
		unordered_map<double, long> bidrecord, askrecord;
		for (int i = 0; i < bid.size(); i++) {
			if (bidrecord.find(bid[i].GetPrice()) != bidrecord.end())
				bidrecord[bid[i].GetPrice()] += bid[i].GetQuantity();
			else {
				bidrecord[bid[i].GetPrice()] = bid[i].GetQuantity();
			}
		}
		for (int i = 0; i < ask.size(); i++) {
			if (askrecord.find(ask[i].GetPrice()) != askrecord.end())
				askrecord[ask[i].GetPrice()] += ask[i].GetQuantity();
			else {
				askrecord[ask[i].GetPrice()] = ask[i].GetQuantity();
			}
		}
		vector<Order> bid_, ask_;
		for (auto& it : bidrecord) {
			bid_.push_back(Order(it.first, it.second, BID));
		}
		for (auto& it : askrecord) {
			ask_.push_back(Order(it.first, it.second, OFFER));
		}

		auto b = orderbook.GetProduct();
		return OrderBook<Bond>(b, bid_, ask_);
	}
};