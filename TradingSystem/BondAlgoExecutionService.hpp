#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AlgoExecution.hpp"
using namespace std;

class BondAlgoExecutionService : public Service<string, AlgoExecution> {
private:
	map<string, AlgoExecution> algoMap;
	vector<ServiceListener<AlgoExecution>*> listenerList;
public:
	BondAlgoExecutionService() {
		algoMap = map<string, AlgoExecution>();

	}
	BondAlgoExecutionService(map<string, AlgoExecution> _algoMap, vector<ServiceListener<AlgoExecution>*> _listenerList) {
		algoMap = _algoMap;
		listenerList = _listenerList;
	}
	AlgoExecution& GetData(string id) {
		return algoMap[id];
	}
	void OnMessage(AlgoExecution& x) {
		return;
	}
	void AddListener(ServiceListener<AlgoExecution>* listener) {
		listenerList.push_back(listener);
		return;
	}
	const vector<ServiceListener<AlgoExecution>*>& GetListeners() const {
		return listenerList;
	}
	void AddOrderBook(OrderBook<Bond>& orderbook) {
		auto id = orderbook.GetProduct().GetProductId();
		auto it = algoMap.find(id);
		if (it != algoMap.end()) {
			(it->second).RunAlgo(orderbook);
		}
		else {
			auto exeorder = ExecutionOrder<Bond>(orderbook.GetProduct(), BID, "0", FOK, 0, 0, 0, "0", true);
			algoMap.insert(pair<string, AlgoExecution >(id, AlgoExecution(exeorder)));
			AddOrderBook(orderbook);
			return;
		}
		for (auto& listener : listenerList) {
			listener->ProcessAdd(it->second);
		}
		return;
	}
};