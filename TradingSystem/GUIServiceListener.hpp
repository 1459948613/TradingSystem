#pragma once
#include "soa.hpp"
#include "GUIService.hpp"
using namespace std;

class GUIServiceListener : public ServiceListener<Price<Bond>> {
private:
	GUIService* gUIService;
public:
	GUIServiceListener(GUIService* _gUIService) {
		gUIService = _gUIService;
	}
	virtual void ProcessAdd(Price<Bond>& price) override {
		gUIService->SendToThrottle(price);
		return;
	}
	virtual void ProcessRemove(Price<Bond>&) override {};
	virtual void ProcessUpdate(Price<Bond>&) override {};
};