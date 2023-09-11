{
 TH1D* pl1Eff=new TH1D("Pl1eff","Plane 1 efficiency in each wedge (Pl. 0+3 on);Wedge number;Efficiency",16,-0.5,15.5);
 TH1D* pl2Eff=new TH1D("Pl2eff","Plane 2 efficiency in each wedge (Pl. 0+3 on);Wedge number;Efficiency",16,-0.5,15.5);
 double em1[16]={438,48,227,445,453,378,109,51,415,526,152,310,298,239,151,254};
 double em2[16]={492,44,302,391,  0,375,113,71,190,483,144,329,286,215,148,274};
 int en[16]=    {500,48,304,447,460,384,118,72,454,542,152,329,303,262,153,277};
 for (int i=0;i<16;i++)
 {
	 double eff1=em1[i]/en[i];
	 double eff2=em2[i]/en[i];
	 double v13=(em1[i]+2)/(en[i]+3);
	 double v12=(em1[i]+1)/(en[i]+2);
	 double std1=sqrt((v13-v12)*v12);
	 double v23=(em2[i]+2)/(en[i]+3);
	 double v22=(em2[i]+1)/(en[i]+2);
	 double std2=sqrt((v23-v22)*v22);
	 pl1Eff->SetBinContent(i+1,eff1);
	 pl2Eff->SetBinContent(i+1,eff2);
	 pl1Eff->SetBinError(i+1,std1);
	 pl2Eff->SetBinError(i+1,std2);
 }
TCanvas MyC;
gStyle->SetOptStat(0);
//ThreeOfFour->GetYaxis()->SetRangeUser(0.57,0.72);
pl1Eff->Draw();
MyC.Print("middlePlanes-Pl1Eff-given0+3-try1.pdf");
MyC.Print("middlePlanes-Pl1Eff-given0+3-try1.png");
pl2Eff->Draw();
MyC.Print("middlePlanes-Pl2Eff-given0+3-try1.pdf");
MyC.Print("middlePlanes-Pl2Eff-given0+3-try1.png");
}
