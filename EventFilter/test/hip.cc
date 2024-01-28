{
 TH1D* Eff24=new TH1D("Eff24",">=2/4 Plane efficiency (TOTEM preliminary);Wedge number;Efficiency",16,-0.5,15.5);
 TH1D* Eff34=new TH1D("Eff34",">=3/4 Plane efficiency (TOTEM preliminary);Wedge number;Efficiency",16,-0.5,15.5);
 TH1D* Eff44=new TH1D("Eff44","4/4 Plane efficiency (TOTEM preliminary);Wedge number;Efficiency",16,-0.5,15.5);
const double pl3[16]={0.923943662,0.175347222,0.818181818,0.865030675,0.874145007,0.781055901,0.912547529,0.294656489,0.935828877,0.953383459,0.490467938,0.805642633,0.76744186,0.740554156,0.761811024,0.665749656};
const double er3[16]={0.010005631,0.015856687,0.016796422,0.013407664,0.01229351,0.01629338,0.017629842,0.017796877,0.012848231,0.008275106,0.020775572,0.015670729,0.017861843,0.021977065,0.018890408,0.017477322};
const double pl2[16]={0.926553672,0.89380531,0.874493927,0.822157434,0.,0.929759704,0.916030534,0.946078431,0.543478261,0.852150538,0.933993399,0.939670932,0.899371069,0.816666667,0.818181818,0.964143426};
const double er2[16]={0.009863556,0.029528502,0.014951769,0.014608129,0.001527884,0.011080225,0.0173568,0.016319084,0.019598206,0.013029883,0.014498444,0.010286918,0.013846179,0.020412078,0.017747453,0.00848404};
const double pl1[16]={0.798022599,0.946902655,0.710526316,0.922740525,0.98006135,0.946395564,0.916030534,0.779411765,0.894409938,0.911290323,0.851485149,0.92321755,0.94129979,0.905555556,0.877378436,0.93625498};
const double er1[16]={0.015090456,0.022296185,0.020381256,0.010253197,0.005659628,0.009804384,0.0173568,0.029016378,0.01215246,0.010468017,0.02049186,0.01146705,0.010896899,0.015532691,0.015133285,0.0110185};
const double pl0[16]={0.81884058,0.743055556,0.776548673,0.847389558,0.805800757,0.795031056,0.370942813,0.81122449,0.837209302,0.860406091,0.883561644,0.737226277,0.834572491,0.646825397,0.787476281,0.779436153};
const double er0[16]={0.014670158,0.036314877,0.019587937,0.013172591,0.014050943,0.015908757,0.01896584,0.027987206,0.014088149,0.012363917,0.018887106,0.016806601,0.016037535,0.021255703,0.017819814,0.016882252};


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
Eff24->GetYaxis()->SetRangeUser(0.,1.01);
Eff24->Draw();
MyC.Print("TwoOfFourPlaneEfficiencies-full.pdf");
Eff34->GetYaxis()->SetRangeUser(0.,1.01);
Eff34->Draw();
MyC.Print("ThreeOfFourPlaneEfficiencies-full.pdf");
Eff44->GetYaxis()->SetRangeUser(0.,1.01);
Eff44->Draw();
MyC.Print("AllFourPlaneEfficiencies-full.pdf");
}
