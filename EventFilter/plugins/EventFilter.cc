#include <memory>
#include <iostream>
#include <map>
#include <bitset>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDFilter.h"

#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include "DataFormats/CTPPSDetId/interface/TotemT2DetId.h"
#include "DataFormats/TotemReco/interface/TotemT2Digi.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "DataFormats/Scalers/interface/Level1TriggerScalers.h"
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
  edm::EDGetTokenT<Level1TriggerScalersCollection> l1scToken_;
  const edm::EDGetTokenT<edmNew::DetSetVector<TotemT2Digi>> digiToken_;

};

EventFilter::EventFilter(const edm::ParameterSet& iConfig) : tracksToken_(consumes<std::vector<CTPPSLocalTrackLite>>(iConfig.getUntrackedParameter<edm::InputTag>("tracks"))),
																		  tracksToken2_(consumes<edm::DetSetVector<TotemRPLocalTrack>>(iConfig.getUntrackedParameter<edm::InputTag>("tracks2"))),
																		  l1scToken_(consumes<Level1TriggerScalersCollection>(iConfig.getUntrackedParameter<edm::InputTag>("l1"))),
                digiToken_(consumes<edmNew::DetSetVector<TotemT2Digi>>(iConfig.getParameter<edm::InputTag>("digisTag")))
{
}

EventFilter::~EventFilter()
{
}


bool EventFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

	bool status = false ;
	bool T2status = false ;

  using namespace edm;

  const EventNumber_t event_number = iEvent.id().event() ;
  const RunNumber_t run_number = iEvent.run() ;
  const int bx = iEvent.bunchCrossing() ;
  const edm::Timestamp tt = iEvent.time() ;
  bitset<64> bsGood;
  bsGood.reset();

  for([[maybe_unused]] const auto& track : iEvent.get(tracksToken_))
  {
	   status = true ;
  }

  for(const auto& track : iEvent.get(tracksToken2_))
  {
	  for([[maybe_unused]] const auto& track2 : track)
	  {
		status = true ;	  
	  }
  }
  for (const auto& l1 : iEvent.get(l1scToken_)) {
//     if (! (event_number%1000)) {
       const auto tr=l1.gtTriggers();
       const auto ev=l1.gtEvents();
       cout<<"Processing Level1 scalers for event "<<event_number<<", triggerNr/eventNr at L1 are= "<<tr<<" / "<<ev<<endl;
//     }
  }

  unsigned int goodT2digis=0;
  std::map<int,int> wedges;
  for (const auto& ds_digis : iEvent.get(digiToken_)) {
    if (!ds_digis.empty()) {
      const TotemT2DetId detid(ds_digis.detId());
      const TotemT2DetId planeId(detid.planeId());
      const auto arm=detid.arm();
      const auto pl=detid.plane();
      const auto ch=detid.channel();
      const auto odd=(pl % 2);
      const auto bsi=(pl-odd)/2;
      const auto wedge=8*arm+2*ch + odd;
      for (const auto& digi : ds_digis) {
        if (digi.hasLE()) { //nonempty T2 digi
          T2status=true;
          if (digi.hasTE()) { //good T2 digi
           goodT2digis++;
	   bsGood.set(wedge*4+bsi);
	   if (! (event_number % 5000))
		   cout<<"Bitset fill ev="<<event_number<<" good digis="<<goodT2digis<<"(plane,wedge,bsindex)=("<<pl<<","
			   <<wedge<<","<<bsi<<"(L),"<<(wedge*4+bsi)<<"(tot)), bs="<<bsGood.to_string()<<endl;
	   if (wedges.count(wedge))
             wedges[wedge]++;
	   else
             wedges[wedge]=1;
	  }
	}
      }
    }
  }
  if (true) {
	  cout<<"Processing event "<<event_number<<" in run "<<run_number<<", bucket "<<bx
	  <<", time is: "<<tt.value()<<" (unix seconds: "<<tt.unixTime()<<", microsec: "<<tt.microsecondOffset()
		  <<"). T2 digis: "<< (T2status ? "some (LE=on) " : "empty") << ", Good T2 digis (LE,TE=on)="
		  << goodT2digis << ", num wedges active: " << wedges.size() << endl;
	  cout<< "Active wedges (arm*8 + channel*2 + (plane%2)):";
	  if (wedges.size()) {
             for (auto it=wedges.begin() ; it!=wedges.end() ; it++)
                cout<<" ww" << it->first;
             cout<<endl;
	  }
	  if ((wedges.size()==1)&&(goodT2digis>1)) {
             const auto ww=(wedges.begin())->first;
             cout<<"1wedge2digis, test eff: " << ww << ", bs="; // <<bsGood.to_string();
             for (auto i=4*ww ; i<4*ww+4; i++)
               cout<<(bsGood.test(i) ? "1" : "0");
             cout<<endl;
	  }
  }

  if (! (event_number % 2)) {
   if (status)
     cout << "RP activity saved" << endl ;
   else
     cout << "RP no activity" << endl ;
  }

  return T2status;
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
