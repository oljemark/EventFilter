#include <TFile.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TProfile.h>
#include <sstream>
#include <string>
#include <iostream>

int stdCh() {
 TFile f("digiHistosT2-4800kEv-r585ZB.root");
 TCanvas MyC;
 std::string pre="chLEtot_";
 int done=0;
 TH1D le3("LE3","LE 13ns;nT2 channel number;ToT profile/channel (ns)",65,-0.5,64.5);
 TH1D le4("LE4","LE 19ns;nT2 channel number;ToT profile/channel (ns)",65,-0.5,64.5);
 TH1D le5("LE5","LE 25ns;nT2 channel number;ToT profile/channel (ns)",65,-0.5,64.5);
 TH1D le6("LE6","LE 31ns;nT2 channel number;ToT profile/channel (ns)",65,-0.5,64.5);
 TH1D le7("LE7","LE 38ns;nT2 channel number;ToT profile/channel (ns)",65,-0.5,64.5);
 for (int u=0;u<64;u++)
 {
	 std::stringstream titl;
	 titl<<pre;
	 titl<<u;
	 titl<<";1";
	 std::cout<<titl.str()<<std::endl;
	 auto chs=f.Get<TH2D>(titl.str().c_str());
	 auto px=chs->ProfileX("",1,-1,"s");
	  le3.SetBinContent(done+0.0,px->GetBinContent(3));
	  le4.SetBinContent(done+0.0,px->GetBinContent(4));
	  le5.SetBinContent(done+0.0,px->GetBinContent(5));
	  le6.SetBinContent(done+0.0,px->GetBinContent(6));
	  le7.SetBinContent(done+0.0,px->GetBinContent(7));
	  le3.SetBinError(done+0.0,px->GetBinError(3));
	  le4.SetBinError(done+0.0,px->GetBinError(4));
	  le5.SetBinError(done+0.0,px->GetBinError(5));
	  le6.SetBinError(done+0.0,px->GetBinError(6));
	  le7.SetBinError(done+0.0,px->GetBinError(7));
	  done++;
 }
 le3.Draw();
 MyC.Print("Bin3-profileStd-per-ch.pdf");
 MyC.Print("Bin3-profileStd-per-ch.png");
 MyC.Print("Bin3-profileStd-per-ch.C");
 le4.Draw();
 MyC.Print("Bin4-profileStd-per-ch.pdf");
 MyC.Print("Bin4-profileStd-per-ch.png");
 MyC.Print("Bin4-profileStd-per-ch.C");
 le5.Draw();
 MyC.Print("Bin5-profileStd-per-ch.pdf");
 MyC.Print("Bin5-profileStd-per-ch.png");
 MyC.Print("Bin5-profileStd-per-ch.C");
 le6.Draw();
 MyC.Print("Bin6-profileStd-per-ch.pdf");
 MyC.Print("Bin6-profileStd-per-ch.png");
 MyC.Print("Bin6-profileStd-per-ch.C");
 le7.Draw();
 MyC.Print("Bin7-profileStd-per-ch.pdf");
 MyC.Print("Bin7-profileStd-per-ch.png");
 MyC.Print("Bin7-profileStd-per-ch.C");
 return done;
}
