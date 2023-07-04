#include <memory>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "DataFormats/CTPPSReco/interface/CTPPSLocalTrackLite.h"
#include "DataFormats/CTPPSReco/interface/TotemRPLocalTrack.h"


//
// class declaration
//

using namespace std;

class EventFilter : public edm::stream::EDFilter<> {
public:
  explicit EventFilter(const edm::ParameterSet&);
  ~EventFilter() override;

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:

  void beginStream(edm::StreamID) override;
  bool filter(edm::Event&, const edm::EventSetup&) override;
  void endStream() override;

  edm::EDGetTokenT<std::vector<CTPPSLocalTrackLite>> tracksToken_;
  edm::EDGetTokenT<edm::DetSetVector<TotemRPLocalTrack>> tracksToken2_;

};

EventFilter::EventFilter(const edm::ParameterSet& iConfig) : tracksToken_(consumes<std::vector<CTPPSLocalTrackLite>>(iConfig.getUntrackedParameter<edm::InputTag>("tracks"))),
																							tracksToken2_(consumes<edm::DetSetVector<TotemRPLocalTrack>>(iConfig.getUntrackedParameter<edm::InputTag>("tracks2")))
{
}

EventFilter::~EventFilter()
{
}


bool EventFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

	bool status = false ;

  using namespace edm;

  EventNumber_t event_number = iEvent.id().event() ;
  RunNumber_t run_number = iEvent.run() ;
  int bx = iEvent.bunchCrossing() ;
  edm::Timestamp tt = iEvent.time() ;

  for(const auto& track : iEvent.get(tracksToken_))
  {
	   status = true ;
  }

  for(const auto& track : iEvent.get(tracksToken2_))
  {
	  for(const auto& track2 : track)
	  {
		status = true ;	  
	  }
  }
  if (! (event_number%4000)) cout<<"Processing event "<<event_number<<" in run "<<run_number<<", bucket "<<bx
	  <<", time is: "<<tt.value()<<" (unix seconds: "<<tt.unixTime()<<", microsec: "<<tt.microsecondOffset()
		  <<")"<<endl;

  // if(status) cout << "RP activity saved" << endl ;
  // else
  // cout << "RP no activity" << endl ;

  return status;
}

void EventFilter::beginStream(edm::StreamID)
{
}

void EventFilter::endStream()
{
}

void EventFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(EventFilter);
