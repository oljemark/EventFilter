{
 TH1D* pl0Eff=new TH1D("pl0eff","Plane 0 efficiency in each wedge (Pl. 1+2 on);Wedge number;Efficiency",16,-0.5,15.5);
 TH1D* pl3Eff=new TH1D("pl3eff","Plane 3 efficiency in each wedge (Pl. 1+2 on);Wedge number;Efficiency",16,-0.5,15.5);
 double em1[16]={446,362,272,431,0,452,107,144,192,485,404,376,362,220,278,427};
 double em2[16]={460, 47,296,425,0,456,399, 54,202,502,170,362,351,295,228,286};
 int en[16]=    {476,391,373,471,0,559,419,156,221,517,476,453,466,331,489,490};
 for (int i=0;i<16;i++)
 {
	 double eff1=(em1[i]+1)/(en[i]+2);
	 double eff2=(em2[i]+1)/(en[i]+2);
	 double v13=(em1[i]+2)/(en[i]+3);
	 double v12=(em1[i]+1)/(en[i]+2);
	 double std1=sqrt((v13-v12)*v12);
	 double v23=(em2[i]+2)/(en[i]+3);
	 double v22=(em2[i]+1)/(en[i]+2);
	 double std2=sqrt((v23-v22)*v22);
	 pl0Eff->SetBinContent(i+1,eff1);
	 pl3Eff->SetBinContent(i+1,eff2);
	 pl0Eff->SetBinError(i+1,std1);
	 pl3Eff->SetBinError(i+1,std2);
 }
TCanvas MyC;
gStyle->SetOptStat(0);
//ThreeOfFour->GetYaxis()->SetRangeUser(0.57,0.72);
pl0Eff->Draw();
MyC.Print("outerPlanes-pl0Eff-given1+2-try1.pdf");
MyC.Print("outerPlanes-pl0Eff-given1+2-try1.png");
pl3Eff->Draw();
MyC.Print("outerPlanes-pl3Eff-given1+2-try1.pdf");
MyC.Print("outerPlanes-pl3Eff-given1+2-try1.png");
}
