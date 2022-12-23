#pragma once
#include <string>
#include <map>
#include <vector>
#include "soa.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "products.hpp"
#include "inquiryservice.hpp"
using namespace std;

class BondInquiryService : public InquiryService<Bond> {
private:
	map<string, Inquiry<Bond>> inquiryMap;
	vector<ServiceListener<Inquiry<Bond>>*> listenerList;
public:
	BondInquiryService() {
		inquiryMap = map<string, Inquiry<Bond> >();
	}
	virtual Inquiry<Bond>& GetData(string id) override {
		return inquiryMap[id];
	}
	virtual void OnMessage(Inquiry<Bond>& inquiry) override {
		inquiry.SetState(inquiry.GetPrice(), DONE);
		inquiryMap.insert(pair<string, Inquiry<Bond> >(inquiry.GetInquiryId(), inquiry));
		for (auto& listener : listenerList) {
			listener->ProcessAdd(inquiry);
		}
		return;
	}
	virtual void AddListener(ServiceListener<Inquiry<Bond>>* listener) override {
		listenerList.push_back(listener);
		return;
	}
	virtual const vector<ServiceListener<Inquiry<Bond>>*>& GetListeners() const {
		return listenerList;
	}
	virtual void SendQuote(const string& inquiryId, double price) override {}
	virtual void RejectInquiry(const string& inquiryId) override {}
};