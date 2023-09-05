#include <memory>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "DataFormats/CTPPSReco/interface/CTPPSLocalTrackLite.h"
#include "DataFormats/CTPPSReco/interface/TotemRPLocalTrack.h"

#include "DataFormats/CTPPSDetId/interface/TotemRPDetId.h"


#include "TFile.h"
#include "TTree.h"

using reco::TrackCollection;

class MyEventAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>
{
public:
  explicit MyEventAnalyzer(const edm::ParameterSet&);
  ~MyEventAnalyzer() override;

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:

  edm::EDGetTokenT<std::vector<CTPPSLocalTrackLite>> tracksToken_;
  edm::EDGetTokenT<edm::DetSetVector<TotemRPLocalTrack>> tracksToken2_;
  std::string diagonal;
  std::string outputFileName;  
  
  void beginJob() override;
  void analyze(const edm::Event&, const edm::EventSetup&) override;
  void endJob() override;

  TTree *tree ;

  Bool_t valid_left_near ;
  Double_t x_ln ;
  Double_t y_ln ;

  Bool_t valid_left_far ;
  Double_t x_lf ;
  Double_t y_lf ;

  Bool_t valid_right_near ;
  Double_t x_rn ;
  Double_t y_rn ;

  Bool_t valid_right_far ;
  Double_t x_rf ;
  Double_t y_rf ;

};


MyEventAnalyzer::MyEventAnalyzer(const edm::ParameterSet& iConfig) : tracksToken_(consumes<std::vector<CTPPSLocalTrackLite>>(iConfig.getUntrackedParameter<edm::InputTag>("tracks"))),
                                              tracksToken2_(consumes<edm::DetSetVector<TotemRPLocalTrack>>(iConfig.getUntrackedParameter<edm::InputTag>("tracks2"))),
                                              diagonal(iConfig.getParameter<std::string>("diagonal")),
                                              outputFileName(iConfig.getParameter<std::string>("outputFileName"))
{
}

MyEventAnalyzer::~MyEventAnalyzer()
{
}


void MyEventAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;

	valid_right_near = false ;
	valid_left_near = false ;

	valid_right_far = false ;
	valid_left_far = false ;
  
  for(const auto& track : iEvent.get(tracksToken2_))
  {
    TotemRPDetId rpId(track.detId());
    unsigned int rpDecId = (100*rpId.arm()) + (10*rpId.station()) + (1*rpId.rp());

    for(const auto& track2 : track)
    {
      if(track2.isValid()) 
      {
        if(diagonal.compare("LBRT") == 0)
        {
          if(rpDecId == 104)
          {
            valid_right_near = true ;
            x_rn = track2.x0() ;
            y_rn = track2.y0() ;
          }
          else if(rpDecId == 5)
          {
            valid_left_near = true ;
            x_ln = track2.x0() ;
            y_ln = track2.y0() ;
          }
          else if(rpDecId == 124)
          {
            valid_right_far = true ;
            x_rf = track2.x0() ;
            y_rf = track2.y0() ;
          }
          else if(rpDecId == 25)
          {
            valid_left_far = true ;
            x_lf = track2.x0() ;
            y_lf = track2.y0() ;
          }
        }
        else if(diagonal.compare("LTRB") == 0)
        {
          if(rpDecId == 105)
          {
            valid_right_near = true ;
            x_rn = track2.x0() ;
            y_rn = track2.y0() ;
          }
          else if(rpDecId == 4)
          {
            valid_left_near = true ;
            x_ln = track2.x0() ;
            y_ln = track2.y0() ;
          }
          else if(rpDecId == 125)
          {
            valid_right_far = true ;
            x_rf = track2.x0() ;
            y_rf = track2.y0() ;
          }
          else if(rpDecId == 24)
          {
            valid_left_far = true ;
            x_lf = track2.x0() ;
            y_lf = track2.y0() ;
          }
        }
      }
    }
  }

  if(valid_left_near && valid_left_far && valid_right_far && valid_right_near)
  {
    tree->Fill() ; 
  }
}

void MyEventAnalyzer::beginJob()
{

  tree = new TTree("TReducedNtuple", "TReducedNtuple") ;  
  
  tree->Branch("track_right_far_valid", &valid_right_far,     "track_right_far_valid/O") ;
  tree->Branch("track_right_far_x",     &x_rf,                "track_right_far_x/D") ;
  tree->Branch("track_right_far_y",     &y_rf,                "track_right_far_y/D") ;

  tree->Branch("track_left_far_valid",  &valid_left_far,      "track_left_far_valid/O") ;
  tree->Branch("track_left_far_x",      &x_lf,                "track_left_far_x/D") ;
  tree->Branch("track_left_far_y",      &y_lf,                "track_left_far_y/D") ;

  tree->Branch("track_right_near_valid",&valid_right_near,    "track_right_near_valid/O") ;
  tree->Branch("track_right_near_x",    &x_rn,                "track_right_near_x/D") ;
  tree->Branch("track_right_near_y",    &y_rn,                "track_right_near_y/D") ;

  tree->Branch("track_left_near_valid", &valid_left_near,     "track_left_near_valid/O") ;
  tree->Branch("track_left_near_x",     &x_ln,                "track_left_near_x/D") ;
  tree->Branch("track_left_near_y",     &y_ln,                "track_left_near_y/D") ;
  
}

void MyEventAnalyzer::endJob()
{
  TFile * f_out = TFile::Open(outputFileName.c_str(), "RECREATE");
  
  tree->Write() ;    
  
  delete f_out ;

}

void MyEventAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(MyEventAnalyzer);
