#include <memory>
#include <iostream>
#include <map>
#include <bitset>
#include <string>

// user include files
#include <TH2D.h>
#include <TH1D.h>
#include <TFile.h>

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

  static constexpr double T2_BIN_WIDTH_NS_ = 25. / 4;
  TH2D noiseLE, multiLE, smultiLE;
  TH2D noiseTE, multiTE, smultiTE;
  TH1D noiseRate;
  std::map<int,TH2D> chLEtot;
};

EventFilter::EventFilter(const edm::ParameterSet& iConfig) : tracksToken_(consumes<std::vector<CTPPSLocalTrackLite>>(iConfig.getUntrackedParameter<edm::InputTag>("tracks"))),
																		  tracksToken2_(consumes<edm::DetSetVector<TotemRPLocalTrack>>(iConfig.getUntrackedParameter<edm::InputTag>("tracks2"))),
																		  l1scToken_(consumes<Level1TriggerScalersCollection>(iConfig.getUntrackedParameter<edm::InputTag>("l1"))),
                digiToken_(consumes<edmNew::DetSetVector<TotemT2Digi>>(iConfig.getParameter<edm::InputTag>("digisTag")))
{
	const double s=0.5*T2_BIN_WIDTH_NS_;
	noiseRate=TH1D("noiseRate","Rate per channel to be 1/4 in wedge;nT2 channel (4*wedge+pl. in wedge,-1=total events);Events",66,-1.5,64.5);
	noiseLE=TH2D("noiseLE","LE distribution if 1/4 in wedge;nT2 channel (4*wedge+pl. in wedge);Leading Edge(ns)",65,-0.5,64.5,33,-25.-s,175.+s);
	multiLE=TH2D("multiLE","LE distribution if >1/4 in wedge;nT2 channel (4*wedge+pl. in wedge);Leading Edge(ns)",65,-0.5,64.5,33,-25.-s,175.+s);
	smultiLE=TH2D("fewLE","LE distribution if >1/4 in wedge (up to 5/16 wedges);nT2 channel (4*wedge+pl. in wedge);Leading Edge(ns)",65,-0.5,64.5,33,-25.-s,175.+s);
	noiseTE=TH2D("noiseTE","TE distribution if 1/4 in wedge;nT2 channel (4*wedge+pl. in wedge);Trailing Edge(ns)",65,-0.5,64.5,33,-25.-s,175.+s);
	multiTE=TH2D("multiTE","TE distribution if if >1/4 in wedge;nT2 channel (4*wedge+pl. in wedge);Trailing Edge(ns)",65,-0.5,64.5,33,-25.-s,175.+s);
	smultiTE=TH2D("fewTE","TE distribution if if >1/4 in wedge (up to 5/16 wedges);nT2 channel (4*wedge+pl. in wedge);Trailing Edge(ns)",65,-0.5,64.5,33,-25.-s,175.+s);
        chLEtot.clear();
	for (int i=0;i<64;i++) {
         std::string nam,titl;
	 nam="chLEtot_";
	 nam.append(std::to_string(i));
	 titl="LE vs tot for channel ";
	 titl.append(std::to_string(i));
	 titl.append(", arm=");
	 titl.append((i/32) ? "5-6" : "4-5");
	 titl.append(", plane=");
	 titl.append(std::to_string((i%32)/4));
	 titl.append(", ch=");
	 titl.append(std::to_string(i%4));
	 titl.append(";Leading Edge (ns);Time over Threshold (ns)");
	 chLEtot[i]=TH2D(nam.c_str(),titl.c_str(),17,-s,100+s,33,-100.-s,100.+s);
	}
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
  std::map<int,float> LEdges;
  std::map<int,float> TEdges;
  for (const auto& ds_digis : iEvent.get(digiToken_)) {
     const double p0[64]={105.905,103.446,99.2012,101.431,110.607,103.052,98.6157,115.257,110.044,104.103,94.7829,107.699,111.723,117.958,100.193,99.2175,
	 123.662,104.944,50.,111.529,104.852,108.577,98.9715,117.875,124.12,109.138,109.224,115.525,90.5432,113.128,105.81,93.5588,83.1318,85.4597,
	 84.83,93.4103,85.686,86.907,88.1821,101.546,85.8877,85.3507,82.3997,92.7767,90.7742,92.7982,87.5735,96.5943,92.6675,85.7291,88.1251,100.792,
	 88.3891,88.8163,91.6619,103.913,92.2972,92.6553,87.8767,93.4001,99.0651,90.3839,89.2728,94.3758};

    const double p1[64]={-2.23358,-2.14968,-1.99853,-2.06289,-2.33729,-2.17111,-1.98558,-2.49849,-2.33486,-2.15859,-1.87143,-2.31735,-2.41831,-2.58514,
	-2.03566,-2.01594,-2.73494,-2.19588,-5.,-2.423,-2.21459,-2.31166,-2.01716,-2.59355,-2.74318,-2.29707,-2.28681,-2.51903,-1.55417,-2.43759,
	-2.18598,-1.8116,-1.63796,-1.66525,-1.69557,-1.95843,-1.6394,-1.73069,-1.79775,-2.12092,-1.70443,-1.6132,-1.55293,-1.89967,-1.83703,-1.87174,
	-1.78382,-1.99482,-1.83933,-1.68918,-1.70917,-2.09607,-1.74401,-1.72821,-1.86512,-2.1693,-1.89157,-1.80474,-1.76403,-1.89563,-2.01352,
	-1.80108,-1.81861,-1.93399};

    if (!ds_digis.empty()) {
      const TotemT2DetId detid(ds_digis.detId());
      const TotemT2DetId planeId(detid.planeId());
      const auto arm=detid.arm();
      const auto pl=detid.plane();
      const auto ch=detid.channel();
      const auto odd=(pl % 2);
      const auto bsi=(pl-odd)/2;
      const auto chi=ch+4*pl+32*arm;
      const auto wedge=8*arm+2*ch + odd;
      const bool flipCh=((pl==3)&&(ch==1)); //LE & TE bits flipped in both arms
      for (const auto& digi : ds_digis) {
        if ((digi.hasLE())||(flipCh&&digi.hasTE())) { //nonempty T2 digi
          T2status=true;
	  T2arm[arm]=true;
          if ((digi.hasTE())||(flipCh&&digi.hasLE())) { //good T2 digi
	   const auto le=digi.leadingEdge();
	   const auto te=digi.trailingEdge();
	   const auto lens=(flipCh ? (te *T2_BIN_WIDTH_NS_) : (le *T2_BIN_WIDTH_NS_));
	   const auto tens=(flipCh ? (le *T2_BIN_WIDTH_NS_) : (te *T2_BIN_WIDTH_NS_));
           const auto totns=tens-lens;
	   const auto signalCenter=p0[chi]+lens*p1[chi];
	   const bool sigRegion=(fabs(totns-signalCenter)<2*6.25); //raw signal ToT sigma=0.94 ... 0.98*binning 6.25
							   // in LE, pre-peak region .LT. 18ns sigma ~ 1.2*6.25
	   if (sigRegion) {
             goodT2digis++;
  	     if (!flipCh)
	      TEdges[wedge*4+bsi]=digi.trailingEdge()*T2_BIN_WIDTH_NS_;
	     else
	      TEdges[wedge*4+bsi]=digi.leadingEdge()*T2_BIN_WIDTH_NS_;
	     if (!flipCh)
	      LEdges[wedge*4+bsi]=digi.leadingEdge()*T2_BIN_WIDTH_NS_; //am interested in good T2 digis only
	     else
	      LEdges[wedge*4+bsi]=digi.trailingEdge()*T2_BIN_WIDTH_NS_;
             if (true) {
		   if (!chLEtot.count(chi))
                     cerr<<"LE vs tot map not created for ch="<<chi<<endl;
		   else
		     chLEtot[chi].Fill(lens,totns);
	     }


	     if (true) {
	       if ((!le)||(!te)) {
	  	       cout<<"Zero value edge in good T2 digi: LE/TE="<<le<<"/"<<te<<" in arm "<<arm<<", plane "<<pl<<", wedge "
			     <<wedge<<", channel "<<ch<<", flipped channel? "<<flipCh<<endl;
	       }
	       if (te==le)
                 cout << "Overlapping edges found as both valid! LE=TE=" << le <<" in arm "<<arm<<", plane "<<pl<<", wedge "
                      <<wedge<<", channel "<<ch<<", flipped channel? "<<flipCh<<endl;

	     }

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
  }
  if (true) {
         noiseRate.Fill(-1.);
         int mult=0;
         int mult3=0;
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
	       auto w=it->first;
               if (it->second > 1) {
		       for (int bi=0;bi<4;bi++) {
			       if (LEdges.count( w*4+bi))
				       multiLE.Fill(w*4+bi,LEdges[w*4+bi]);
			       if (TEdges.count( w*4+bi))
				       multiTE.Fill(w*4+bi,TEdges[w*4+bi]);
		       }
	       } else {
		       for (int bi=0;bi<4;bi++) {
			       if (LEdges.count( w*4+bi)) {
				       noiseLE.Fill(w*4+bi,LEdges[w*4+bi]);
				       noiseRate.Fill(w*4+bi);
			       }
			       if (TEdges.count( w*4+bi))
				       noiseTE.Fill(w*4+bi,TEdges[w*4+bi]);
		       }
	       }
               cout<<" ww" << it->first;
	       if ((it->second) > 1) {
                  T2mArm[(it->first < 8) ? 0 : 1] = true;
                  cout<<"-mm" << it->first;
		  mult++;
		  mulWedges[it->first]=1;
	       }
	       if ((it->second) > 2) mult3++;
	     }
	  }
          cout<<endl;

          cout<<"T2MultiActivity/arm (4-5/5-6): ("<<T2mArm[0] <<"/"<<T2mArm[1]<<")"<<endl;

	  cout<<"MultiW, multi2/3="<<mult<<"/"<<mult3<<" occupancy=";
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


	  if ((wedges.size())&&mult&&(mult<6)) {
             for (auto it=wedges.begin() ; it!=wedges.end() ; it++) {
	       auto w=it->first;
               if (it->second > 1) {
                 for (int bi=0;bi<4;bi++) {
                   if (LEdges.count( w*4+bi))
                     smultiLE.Fill(w*4+bi,LEdges[w*4+bi]);
                   if (TEdges.count( w*4+bi))
                     smultiTE.Fill(w*4+bi,TEdges[w*4+bi]);
                 }
	       }
	     }
	  }
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
	  if (mult)
            cout<<"Multi2/3="<<mult<<"/"<<mult3<<" bsAny="<<bsGood.to_string()<<endl;
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
	TFile f("file:./digiHistosT2_LEToT_noiseCut.root","RECREATE");
	noiseRate.Write();
	noiseLE.Write();
	noiseTE.Write();
	multiLE.Write();
	multiTE.Write();
	smultiLE.Write();
	smultiTE.Write();
	for (const auto& ch: chLEtot)
          ch.second.Write();
	f.Close();
}

void EventFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(EventFilter);
