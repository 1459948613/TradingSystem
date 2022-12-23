#pragma once
#include "streamingservice.hpp"
#include "pricingservice.hpp"
#include "products.hpp"
#include <iostream>
using namespace std;

class AlgoStream {
private:
	PriceStream<Bond> priceStream;
public:
	AlgoStream() {

	}
	AlgoStream(const PriceStream<Bond>& _priceStream):priceStream(_priceStream) {}

	// run algo to update priceStream according to bond price
	void RunAlgo(Price<Bond> price) {
		auto bond = price.GetProduct();
		if (bond.GetProductId() != priceStream.GetProduct().GetProductId()) {
			return;
		}
		double mid = price.GetMid();
		double spread = price.GetBidOfferSpread();
		double bid = mid - spread / 2.0;
		double offer = mid + spread / 2.0;
		if (spread < 2.5 / 256.0) {
			PriceStreamOrder orderbid(bid, 1000000, 2000000, BID);
			PriceStreamOrder orderask(offer, 1000000, 2000000, OFFER);
			priceStream = PriceStream<Bond>(bond, orderbid, orderask);
		}
		else {
			PriceStreamOrder orderbid(bid, 0, 0, BID);
			PriceStreamOrder orderask(offer, 0, 0, OFFER);
			priceStream = PriceStream<Bond>(bond, orderbid, orderask);
		}
		return;
	}

	// return *priceStream
	PriceStream<Bond> GetPriceStream() const {
		return priceStream;
	}
};