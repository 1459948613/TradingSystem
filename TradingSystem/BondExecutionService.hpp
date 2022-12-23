#pragma once
#include "BondAlgoExecutionService.hpp"
#include "BondExecutionServiceConnector.hpp"
#include "executionservice.hpp"
using namespace std;

class BondExecutionService : public ExecutionService<Bond> {
private:
	map<string, ExecutionOrder<Bond>> executionMap;
	vector<ServiceListener<ExecutionOrder<Bond>>*> listenerList;
	BondExecutionServiceConnector* bondExecutionServiceConnector;
public:
	BondExecutionService(BondExecutionServiceConnector* _bondExecutionServiceConnector) {
		bondExecutionServiceConnector = _bondExecutionServiceConnector;
	}
	virtual ExecutionOrder<Bond>& GetData(string id) override {
		return executionMap[id];
	}
	virtual void OnMessage(ExecutionOrder<Bond>&) override {
		return;
	}
	virtual void AddListener(ServiceListener<ExecutionOrder<Bond> >* listener) override {
		listenerList.push_back(listener);
		return; 
	}
	virtual const vector<ServiceListener<ExecutionOrder<Bond> >*>& GetListeners() const {
		return listenerList;
	}
	void AddAlgoExecution(const AlgoExecution& algo) {
		auto executionOrder = algo.GetExecutionOrder();
		string id = executionOrder.GetProduct().GetProductId();

		if (executionMap.find(id) != executionMap.end())
			executionMap.erase(id);
		executionMap.insert(pair<string, ExecutionOrder<Bond> >(id, executionOrder));

		for (auto& listener : listenerList) {
			listener->ProcessAdd(executionOrder);
		}

		return;
	}
	virtual void ExecuteOrder(ExecutionOrder<Bond>& order, Market market) {
		bondExecutionServiceConnector->Publish(order);
	}
};