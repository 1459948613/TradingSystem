#pragma once
#include <iostream>
#include "historicaldataservice.hpp"
#include "GUIServiceConnector.hpp"
#include "BondStreamingService.hpp"
#include "BondRiskService.hpp"
#include "BondPositionService.hpp"
#include "BondExecutionService.hpp"
#include "BondInquiryService.hpp"
#include "HistoricalPositionConnector.hpp"
#include "HistoricalRiskConnector.hpp"
#include "HistoricalExecutionConnector.hpp"
#include "HistoricalStreamingConnector.hpp"
#include "HistoricalAllInquiriesConnector.hpp"
using namespace std;

class BondHistoricalPositionService : public HistoricalDataService<Position<Bond>> {
private:
	HistoricalPositionConnector* connector;
	map<string, Position<Bond> > dataMap;
public:
	BondHistoricalPositionService(HistoricalPositionConnector* _p) :connector(_p) {}
	virtual Position<Bond>& GetData(string id) override { 
		return dataMap.at(id); 
	}
	virtual void OnMessage(Position<Bond>& bond) override {}
	virtual void AddListener(ServiceListener<Position<Bond>  >* listener) override {}
	virtual const vector<ServiceListener<Position<Bond>  >*>& GetListeners() const {}
	virtual void PersistData(string persistKey, Position<Bond>& data) {
		auto id = data.GetProduct().GetProductId();
		if (dataMap.find(id) != dataMap.end())
			dataMap.erase(id);
		dataMap.insert(pair<string, Position<Bond> >(id, data));
		connector->Publish(data);
		return;
	}
};

class BondHistoricalRiskService : public HistoricalDataService<PV01<Bond>> {
private:
	HistoricalRiskConnector* connector;
	map<string, PV01<Bond> > dataMap;
public:
	BondHistoricalRiskService(HistoricalRiskConnector* _p) :connector(_p) {}
	virtual PV01<Bond>& GetData(string id) override { 
		return dataMap.at(id);
	}
	virtual void OnMessage(PV01<Bond>& bond) override {}
	virtual void AddListener(ServiceListener<PV01<Bond>  >* listener) override {}
	virtual const vector<ServiceListener<PV01<Bond>  >*>& GetListeners() const {}
	virtual void PersistData(string persistKey, PV01<Bond>& data) {
		auto id = data.GetProduct().GetProductId();
		if (dataMap.find(id) != dataMap.end())
			dataMap.erase(id);
		dataMap.insert(pair<string, PV01<Bond> >(id, data));
		connector->Publish(data);
		return;
	}
};

class BondHistoricalExecutionService : public HistoricalDataService<ExecutionOrder<Bond>> {
private:
	HistoricalExecutionConnector* connector;
	map<string, ExecutionOrder<Bond> > dataMap;
public:
	BondHistoricalExecutionService(HistoricalExecutionConnector* _p) :connector(_p) {}
	virtual ExecutionOrder<Bond>& GetData(string id) override { 
		return dataMap.at(id); 
	}
	virtual void OnMessage(ExecutionOrder<Bond>& bond) override {}
	virtual void AddListener(ServiceListener<ExecutionOrder<Bond>  >* listener) override {}
	virtual const vector<ServiceListener<ExecutionOrder<Bond>  >*>& GetListeners() const {}
	virtual void PersistData(string persistKey, ExecutionOrder<Bond>& data) {
		auto id = data.GetOrderId();
		if (dataMap.find(id) != dataMap.end())
			dataMap.erase(id);
		dataMap.insert(pair<string, ExecutionOrder<Bond> >(id, data));
		connector->Publish(data);
		return;
	}
};

class BondHistoricalStreamingService : public HistoricalDataService<PriceStream<Bond>> {
private:
	HistoricalStreamingConnector* connector;
	map<string, PriceStream<Bond> > dataMap;
public:
	BondHistoricalStreamingService(HistoricalStreamingConnector* _p) :connector(_p) {}
	virtual PriceStream<Bond>& GetData(string id) override { 
		return dataMap.at(id); 
	}
	virtual void OnMessage(PriceStream<Bond>& bond) override {}
	virtual void AddListener(ServiceListener<PriceStream<Bond>  >* listener) override {}
	virtual const vector<ServiceListener<PriceStream<Bond>  >*>& GetListeners() const {}
	virtual void PersistData(string persistKey, PriceStream<Bond>& data) {
		auto id = data.GetProduct().GetProductId();
		if (dataMap.find(id) != dataMap.end())
			dataMap.erase(id);
		dataMap.insert(pair<string, PriceStream<Bond> >(id, data));
		connector->Publish(data);
		return;
	}
};

class BondHistoricalAllInquiriesService : public HistoricalDataService<Inquiry<Bond>> {
private:
	HistoricalAllInquiriesConnector* connector;
	map<string, Inquiry<Bond> > dataMap;
public:
	BondHistoricalAllInquiriesService(HistoricalAllInquiriesConnector* _p) :connector(_p) {}
	virtual Inquiry<Bond>& GetData(string id) override { 
		return dataMap.at(id); 
	}
	virtual void OnMessage(Inquiry<Bond>& bond) override {}
	virtual void AddListener(ServiceListener<Inquiry<Bond>  >* listener) override {}
	virtual const vector<ServiceListener<Inquiry<Bond> >*>& GetListeners() const {}
	virtual void PersistData(string persistKey, Inquiry<Bond>& data) {
		auto id = data.GetInquiryId();
		if (dataMap.find(id) != dataMap.end())
			dataMap.erase(id);
		dataMap.insert(pair<string, Inquiry<Bond> >(id, data));

		connector->Publish(data);
		return;
	}
};