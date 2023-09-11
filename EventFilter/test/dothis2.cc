{
TH1D* TwoOfFour=new TH1D("TwoOfFour","Wedge occurrence rate (2..4/4);Wedge number;Occurrence among >0 wedge events",16,-0.5,15.5);
//TwoOfFour.Sumw2();
TwoOfFour->Fill(0.,141858.);
TwoOfFour->Fill(1,140993.);
TwoOfFour->Fill(2,139891.);
TwoOfFour->Fill(3,140900.);
TwoOfFour->Fill(4,135885.);
TwoOfFour->Fill(5,140563.);
TwoOfFour->Fill(6,139120.);
TwoOfFour->Fill(7,137814.);
TwoOfFour->Fill(8,141679.);
TwoOfFour->Fill(9,142723.);
TwoOfFour->Fill(10,140331.);
TwoOfFour->Fill(11,142713.);
TwoOfFour->Fill(12,141679.);
TwoOfFour->Fill(13,139103.);
TwoOfFour->Fill(14,140192.);
TwoOfFour->Fill(15,142258.);
TwoOfFour->Sumw2(kFALSE);
TwoOfFour->Sumw2(kTRUE);
//TwoOfFour.SetBinError(1,sqrt(141858.));
TwoOfFour->Scale(1./196268.);
TCanvas MyC;
TwoOfFour->GetYaxis()->SetRangeUser(0.67,0.75);
TwoOfFour->Draw();
MyC.Print("wedgeDistrib-2-of-4-try3.pdf");
}
