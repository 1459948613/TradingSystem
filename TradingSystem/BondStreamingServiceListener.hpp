#pragma once
#include "BondStreamingService.hpp"
#include "soa.hpp"
using namespace std;

class BondStreamingServiceListener : public ServiceListener<AlgoStream> {
private:
	BondStreamingService* bondStreamingService;

public:
	BondStreamingServiceListener(BondStreamingService* _bondStreamingService) {
		bondStreamingService = _bondStreamingService;
	}
	virtual void ProcessAdd(AlgoStream& algoStream) override {
		bondStreamingService->AddAlgo(algoStream);
		auto priceStream = algoStream.GetPriceStream();
		bondStreamingService->PublishPrice(priceStream);
		return;
	}
	virtual void ProcessRemove(AlgoStream&) override {
		return;
	}
	virtual void ProcessUpdate(AlgoStream&) override {
		return;
	}
};