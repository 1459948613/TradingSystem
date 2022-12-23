#pragma once
#include "streamingservice.hpp"
#include "BondAlgoStreamingService.hpp"
#include "BondStreamingServiceConnector.hpp"
using namespace std;

class BondStreamingService : public StreamingService<Bond> {
private:
	map<string, PriceStream<Bond> > streamMap;
	vector<ServiceListener<PriceStream<Bond> >*> listenerList;
	BondStreamingServiceConnector* bondStreamingServiceConnector;
public:
	BondStreamingService(BondStreamingServiceConnector* _bondStreamingServiceConnector) {
		bondStreamingServiceConnector = _bondStreamingServiceConnector;
		streamMap = map<string, PriceStream<Bond> >();
	}
	virtual PriceStream<Bond>& GetData(string id) override {
		return streamMap[id];
	}
	virtual void OnMessage(PriceStream<Bond>&) override {
		return;
	}
	virtual void AddListener(ServiceListener<PriceStream<Bond> >* listener) override {
		listenerList.push_back(listener);
		return;
	}
	virtual const vector<ServiceListener<PriceStream<Bond> >*>& GetListeners() const {
		return listenerList;
	}
	void AddAlgo(const AlgoStream& algo) {
		auto stream = algo.GetPriceStream();
		auto id = stream.GetProduct().GetProductId();
		if (streamMap.find(id) != streamMap.end())
			streamMap.erase(id);
		streamMap.insert(pair<string, PriceStream<Bond> >(id, stream));
		for (auto& listener : listenerList) {
			listener->ProcessAdd(stream);
		}

		return;
	}
	virtual void PublishPrice(PriceStream<Bond>& priceStream) {
		bondStreamingServiceConnector->Publish(priceStream);
		return;
	}
};