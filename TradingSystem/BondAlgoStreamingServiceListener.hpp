#pragma once
#include "soa.hpp"
#include "BondAlgoStreamingService.hpp"
using namespace std;

class BondAlgoStreamingServiceListener : public ServiceListener<Price<Bond>> {
private:
	BondAlgoStreamingService* bondAlgoStreamingService;
public:
	BondAlgoStreamingServiceListener(BondAlgoStreamingService* _bondAlgoStreamingService) {
		bondAlgoStreamingService = _bondAlgoStreamingService;
	}
	virtual void ProcessAdd(Price<Bond>& price) override {
		bondAlgoStreamingService->AddPrice(price);
		return;
	}
	virtual void ProcessRemove(Price<Bond>& price) override {
		return;
	}
	virtual void ProcessUpdate(Price<Bond>& price) override {
		return;
	}
};