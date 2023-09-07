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
	bool T2arm[2] = {false, false} ;
	bool RParmC[2] = {false, false} ;
	bool RParmT[2] = {false, false} ;
	bool RParmTV[2] = {false, false} ;
        int rph=-1;
	int rpv=-1;

  using namespace edm;

  const EventNumber_t event_number = iEvent.id().event() ;
  const RunNumber_t run_number = iEvent.run() ;
  const int bx = iEvent.bunchCrossing() ;
  const edm::Timestamp tt = iEvent.time() ;
  bitset<64> bsGood;
  bsGood.reset();

  for(const auto& track : iEvent.get(tracksToken_))
  {
	  const CTPPSDetId rp(track.rpId());
	  RParmC[rp.arm()]=true;
	  rph=100*rp.arm()+10*rp.station()+rp.rp();
	  status = true ;
  }

  for(const auto& track : iEvent.get(tracksToken2_))
  {
	  for(const auto& track2 : track)
	  {
		  const CTPPSDetId rp(track.detId());
		  RParmT[rp.arm()]=true;
		  RParmTV[rp.arm()]=track2.isValid();
		  rpv=100*rp.arm()+10*rp.station()+rp.rp();
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
  std::map<int,int> mulWedges;
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
	  T2arm[arm]=true;
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
         int mult=0;
	  cout<<"Processing event "<<event_number<<" in run "<<run_number<<", bucket "<<bx
	  <<", time is: "<<tt.value()<<" (unix seconds: "<<tt.unixTime()<<", microsec: "<<tt.microsecondOffset()
		  <<"). T2 digis: "<< (T2status ? "some (LE=on) " : "empty") << ", Good T2 digis (LE,TE=on)="
		  << goodT2digis << ", num wedges active: " << wedges.size() << endl;
          cout<<"T2Activity/arm (4-5/5-6): ("<<T2arm[0] <<"/"<<T2arm[1]<<")"<<endl;
          cout<<"RPActivity/arm (4-5/5-6), first TrackLite, then RPLocal, and its validity: [C:"<<RParmC[0] <<"/"<<RParmC[1]<<",pot="<<rph<<"|R:"
		  <<RParmT[0] << "/"<< RParmT[1]<<"|R,V:"<< RParmTV[0]<<"/"<<RParmTV[1] <<",potTV="<<rpv<<"]"<<endl;
	  cout<< "Active wedges and multihit wedges (arm*8 + channel*2 + (plane%2)):";

	  bool T2mArm[2]={false, false};

	  if (wedges.size()) {
             for (auto it=wedges.begin() ; it!=wedges.end() ; it++) {
               cout<<" ww" << it->first;
	       if ((it->second) > 1) {
                  T2mArm[(it->first < 8) ? 0 : 1] = true;
                  cout<<"-mm" << it->first;
		  mult++;
		  mulWedges[it->first]=1;
	       }
	     }
	  }
          cout<<endl;

          cout<<"T2MultiActivity/arm (4-5/5-6): ("<<T2mArm[0] <<"/"<<T2mArm[1]<<")"<<endl;

	  cout<<"MultiW, multi="<<mult<<" occupancy=";
	  if (! wedges.size()) {
             cout<<"00000000|";
             cout<<"00000000";
	  }
          else {
           for (int w=0; w<16; w++) {
	   if (wedges.count(w))
             cout<<wedges[w];
	   else
             cout<<"0";
	   if (w==7)
             cout<<"|";
	   }
	  }
          cout<<endl;


	  if (mult>1) {
            //Look for nearest neighbors to cluster
	    for (int arm=0; arm<2; arm++) {
              for (int sec=0; sec<8; sec++) {
                if (mulWedges.count(8*arm+sec) && mulWedges.count(8*arm+((sec+1)%8))) {
                  if (mulWedges[8*arm+sec]) {
                     mulWedges[8*arm+sec]++;
                     mulWedges[8*arm+((sec+1)%8)]--;
		  }
		}
	      }
	    }
	  }

	  if ((wedges.size()==1)&&(goodT2digis>1)) {
             const auto ww=(wedges.begin())->first;
             cout<<"1wedge2digis, test eff: " << ww << ", bs1="; // <<bsGood.to_string();
             for (auto i=4*ww ; i<4*ww+4; i++)
               cout<<(bsGood.test(i) ? "1" : "0");
             cout<<endl;
	  }
	  if (mult==2) {
            cout<<"2wedgeMultiHit";
            for (auto it=wedges.begin() ; it!=wedges.end() ; it++)
             if ((it->second)>1)
              cout<<",qq" << it->first;
            cout<<" bsq="<<bsGood.to_string()<<endl;
	    auto mit=mulWedges.begin();
	    if ((mit->second)>1)
              cout<<"1clusterMHit,clcl"<<(mit->first)<<endl;
	  }
	  if ((mult>2)&&(mult<5)) {
            cout<<"MultiHitClustered: mul="<<mult<<" bsmu="<<bsGood.to_string()<<endl;
            for (auto it=mulWedges.begin() ; it!=mulWedges.end() ; it++)
              cout<<"mumu"<<(it->first)<<"("<<(it->second)<<")";
            cout<<endl;
	  }
	  if ((mult==1)&&(wedges.size() > 1)) {
            cout<<"1wedgeMultiHit";
            for (auto it=wedges.begin() ; it!=wedges.end() ; it++)
             if ((it->second)>1)
              cout<<",pp" << it->first;
            cout<<" bsp="<<bsGood.to_string()<<endl;
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
