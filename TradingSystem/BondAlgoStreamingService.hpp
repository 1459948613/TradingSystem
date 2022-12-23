#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AlgoStream.hpp"
#include "products.hpp"
#include "soa.hpp"
using namespace std;

class BondAlgoStreamingService : public Service<string, AlgoStream> {
private:
	map<string, AlgoStream > algoMap;
	vector<ServiceListener<AlgoStream>* > listenerList;
public:
	BondAlgoStreamingService() {
		algoMap = map<string, AlgoStream>();
	}
	virtual AlgoStream& GetData(string id) override {
		return algoMap[id];
	}
	virtual void OnMessage(AlgoStream&) override {

	}
	virtual void AddListener(ServiceListener<AlgoStream>* listener) override {
		listenerList.push_back(listener);
	}
	virtual const vector<ServiceListener<AlgoStream>*>& GetListeners() const {
		return listenerList;
	}
	void AddPrice(const Price<Bond>& price) {
		auto id = price.GetProduct().GetProductId();
		auto it = algoMap.find(id);
		if (it != algoMap.end()) {
			(it->second).RunAlgo(price);
		}
		else {
			PriceStreamOrder p1(0, 0, 0, BID);
			PriceStreamOrder p2(0, 0, 0, OFFER);
			PriceStream<Bond> ps(price.GetProduct(), p1, p2);
			algoMap.insert(pair<string, PriceStream<Bond> >(id, ps));
			AddPrice(price);
			return;
		}
		for (auto& listener : listenerList) {
			listener->ProcessAdd(it->second);
		}
		return;
	}
};