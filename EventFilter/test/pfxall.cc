#include <TFile.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TProfile.h>
#include <sstream>
#include <string>
#include <iostream>

int fitCh() {
 TFile f("digiHistosT2-4800kEv-r585ZB.root");
 TCanvas MyC;
 gStyle->SetOptFit();
 std::string pre="chLEtot_";
 int done=0;
 for (int u=0;u<64;u++)
 {
	 std::stringstream titl;
	 titl<<pre;
	 titl<<u;
	 titl<<";1";
	 std::cout<<titl.str()<<std::endl;
	 auto chs=f.Get<TH2D>(titl.str().c_str());
	 auto px=chs->ProfileX();
	  px->Fit("pol1","","",22.,40.);
	  px->GetYaxis()->SetRangeUser(0.,75.);
	  px->Draw();
	  std::stringstream prt;
	  prt<<"pfxFit2_ch"<<u;
	  prt<<".png";
	  std::cout<<prt.str()<<std::endl;
	  MyC.Print(prt.str().c_str());
	  done++;
 }
 return done;
}
