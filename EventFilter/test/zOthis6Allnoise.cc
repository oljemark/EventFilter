{
 TH1D* Eff24=new TH1D("Eff24",">=2/4 Plane efficiency in each wedge w/o noise cut;Wedge number;Efficiency",16,-0.5,15.5);
 TH1D* Eff34=new TH1D("Eff34",">=3/4 Plane efficiency in each wedge w/o noise cut;Wedge number;Efficiency",16,-0.5,15.5);
 TH1D* Eff44=new TH1D("Eff44","4/4 Plane efficiency in each wedge w/o noise cut;Wedge number;Efficiency",16,-0.5,15.5);
const double pl3[16]={0.97635605,0.182640145,0.866666667,0.939297125,0.916918429,0.87687188,0.973333333,0.242658423,0.911042945,0.970266041,0.466055046,0.851590106,0.816546763,0.939306358,0.702702703,0.657097289};
const double er3[16]={0.005810472,0.016440326,0.015091149,0.009630549,0.010784355,0.013439163,0.011474289,0.016846231,0.015916956,0.006867114,0.021329528,0.014967911,0.016423802,0.01304527,0.022622323,0.018933307};
const double pl2[16]={0.983193277,0.952830189,0.9844098,0.897709924,0.,0.963436929,0.977678571,0.98125,0.512953368,0.906432749,0.951310861,0.981670061,0.974248927,0.855263158,0.982817869,0.988009592};
const double er2[16]={0.004989767,0.022042391,0.006215601,0.011884052,0.001611604,0.008185945,0.010693714,0.012192543,0.020736612,0.01118193,0.013542807,0.006348982,0.007596431,0.018097111,0.008274041,0.005804046};
const double pl1[16]={0.882352941,0.971698113,0.812917595,0.986259542,0.982200647,0.972577697,0.9375,0.71875,0.91537133,0.964912281,0.981273408,0.928716904,0.984978541,0.923684211,0.982817869,0.93764988};
const double er1[16]={0.012088016,0.018173127,0.018415616,0.004776443,0.005532933,0.007179031,0.016558784,0.035427757,0.011635062,0.007154594,0.009003846,0.011717632,0.005991784,0.013763802,0.008274041,0.011995134};
const double pl0[16]={0.930576071,0.927927928,0.778251599,0.888583219,0.8395574,0.840442338,0.352941176,0.942622951,0.907534247,0.925666199,0.894197952,0.829090909,0.853159851,0.676300578,0.739018088,0.876681614};
const double er0[16]={0.009836285,0.025470488,0.019178066,0.011702218,0.01366275,0.014571479,0.019564736,0.022062544,0.012047108,0.009881866,0.018105992,0.016066157,0.015287414,0.020509681,0.022300678,0.015625039};


 for (int i=0;i<16;i++)
 {
	 const auto eff4=pl0[i]*pl1[i]*pl2[i]*pl3[i];
	 const auto n0=1.-pl0[i];
	 const auto n1=1.-pl1[i];
	 const auto n2=1.-pl2[i];
	 const auto n3=1.-pl3[i];
	 auto eff3=n0*pl1[i]*pl2[i]*pl3[i];
	 eff3+=pl0[i]*n1*pl2[i]*pl3[i];
	 eff3+=pl0[i]*pl1[i]*n2*pl3[i];
	 eff3+=pl0[i]*pl1[i]*pl2[i]*n3;
	 auto eff2=n0*n1*pl2[i]*pl3[i];// 0011 + 1100 + 1010 + 1001 + 0101 + 0110
	 eff2+=pl0[i]*pl1[i]*n2*n3;
	 eff2+=pl0[i]*n1*pl2[i]*n3;
	 eff2+=pl0[i]*n1*n2*pl3[i];
	 eff2+=n0*pl1[i]*n2*pl3[i];
	 eff2+=n0*pl1[i]*pl2[i]*n3;
	 const auto e30=er0[i]*(pl1[i]*pl2[i]+pl1[i]*pl3[i]+pl2[i]*pl3[i]-3*pl1[i]*pl2[i]*pl3[i]);
	 const auto e31=er1[i]*(pl0[i]*pl2[i]+pl0[i]*pl3[i]+pl2[i]*pl3[i]-3*pl0[i]*pl2[i]*pl3[i]);
	 const auto e32=er2[i]*(pl0[i]*pl1[i]+pl0[i]*pl3[i]+pl1[i]*pl3[i]-3*pl0[i]*pl1[i]*pl3[i]);
	 const auto e33=er3[i]*(pl0[i]*pl1[i]+pl0[i]*pl2[i]+pl1[i]*pl2[i]-3*pl0[i]*pl1[i]*pl2[i]);
	 const auto erreff3=sqrt(e30*e30+e31*e31+e32*e32+e33*e33);
	 const auto e40=er0[i]/pl0[i];
	 const auto e41=er1[i]/pl1[i];
	 const auto e42=er2[i]/(pl2[i]>0.000001 ? pl2[i] : 0.001);
	 const auto e43=er3[i]/pl3[i];
	 auto erreff4=eff4*sqrt(e40*e40+e41*e41+e42*e42+e43*e43);
	 if (i==4) 
		 erreff4=pl0[i]*pl1[i]*pl3[i]*er2[i];
	 const auto e20=er0[i]*(3*pl1[i]*pl2[i]*pl3[i]+pl1[i]+pl2[i]+pl3[i]-2*pl1[i]*pl2[i]-2*pl1[i]*pl3[i]-2*pl2[i]*pl3[i]);
	 const auto e21=er1[i]*(3*pl0[i]*pl2[i]*pl3[i]+pl0[i]+pl2[i]+pl3[i]-2*pl0[i]*pl2[i]-2*pl0[i]*pl3[i]-2*pl2[i]*pl3[i]);
	 const auto e22=er2[i]*(3*pl0[i]*pl1[i]*pl3[i]+pl0[i]+pl1[i]+pl3[i]-2*pl0[i]*pl1[i]-2*pl0[i]*pl3[i]-2*pl1[i]*pl3[i]);
	 const auto e23=er3[i]*(3*pl0[i]*pl1[i]*pl2[i]+pl0[i]+pl1[i]+pl2[i]-2*pl0[i]*pl1[i]-2*pl0[i]*pl2[i]-2*pl1[i]*pl2[i]);
	 const auto erreff2=sqrt(e20*e20+e21*e21+e22*e22+e23*e23);
	 Eff24->SetBinContent(i+1,eff2+eff3+eff4);
	 Eff24->SetBinError(i+1,erreff2);
	 Eff34->SetBinContent(i+1,eff3+eff4);
	 Eff34->SetBinError(i+1,erreff3);
	 Eff44->SetBinContent(i+1,eff4);
	 Eff44->SetBinError(i+1,erreff4);
 }

TCanvas MyC;
gStyle->SetOptStat(0);
Eff24->GetYaxis()->SetRangeUser(0.9,1.01);
Eff24->Draw();
MyC.Print("TwoOfFourPlaneEfficiencies-v10noNoiseC.pdf");
MyC.Print("TwoOfFourPlaneEfficiencies-v10noNoiseC.png");
MyC.Print("TwoOfFourPlaneEfficiencies-v10noNoiseC.C");
Eff34->GetYaxis()->SetRangeUser(0.,1.01);
Eff34->Draw();
MyC.Print("ThreeOfFourPlaneEfficiencies-v10noNoiseC.pdf");
MyC.Print("ThreeOfFourPlaneEfficiencies-v10noNoiseC.png");
MyC.Print("ThreeOfFourPlaneEfficiencies-v10noNoiseC.C");
Eff44->GetYaxis()->SetRangeUser(0.,1.01);
Eff44->Draw();
MyC.Print("AllFourPlaneEfficiencies-v10noNoiseC.pdf");
MyC.Print("AllFourPlaneEfficiencies-v10noNoiseC.png");
MyC.Print("AllFourPlaneEfficiencies-v10noNoiseC.C");
}
