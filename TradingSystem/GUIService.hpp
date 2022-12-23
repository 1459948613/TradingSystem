#pragma once
#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/date_time.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "pricingservice.hpp"
#include "soa.hpp"
#include "GUIServiceConnector.hpp"
using namespace std;
using namespace boost::posix_time;

class GUIService :public PricingService<Bond> {
private:
	GUIServiceConnector* gUIServiceConnector;
	ptime lastSendTime;
	time_duration throtteTime;
public:
	GUIService(GUIServiceConnector* _gUIServiceConnector) {
		gUIServiceConnector = _gUIServiceConnector;
		throtteTime = millisec(3);
		lastSendTime = microsec_clock::local_time();
	}
	void SendToThrottle(Price<Bond>& data) {
		ptime timeNow = microsec_clock::local_time();
		time_duration diff = timeNow - lastSendTime;

		if (diff < throtteTime) {
			return;
		}
		lastSendTime = timeNow;
		auto pts = PriceWithTimeStamp(timeNow, data);
		gUIServiceConnector->Publish(pts);

		return;
	}
	virtual Price<Bond>& GetData(string id) override {}
	virtual void OnMessage(Price<Bond>& data) override {}
	virtual void AddListener(ServiceListener<Price<Bond> >* listener) override {}
	virtual const vector< ServiceListener<Price<Bond> >* >& GetListeners() const {}
};
